# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

Rocky MK1 is a 3D-printed, multi-legged walking robot (default: 5 legs, 3 servos each) running on an
ESP32 via the Arduino framework under PlatformIO. It is controlled over a FlySky RC receiver (IBUS).
The README has the hardware/build background; this file covers the code. Comments throughout are in German.

## Build / Flash / Monitor

This is a PlatformIO project (`platformio.ini`, env `default`, board `esp32dev`). The CLI binary may not be
on `PATH` — it ships with the VS Code PlatformIO extension. Common commands:

```bash
pio run                      # compile
pio run -t upload            # compile + flash over USB (upload_speed 460800)
pio device monitor           # serial monitor (115200 baud)
pio run -t clean
```

There is no test suite. Verification is done on hardware via the serial monitor (set `debug = true` in
`definitions.h` to stream parsed RC input each loop).

## Where the code lives — read this first

The robot's kinematics/gait *engine* is **not in this repo**. It is an external library pulled in via
`lib_extra_dirs = ../libraries` in `platformio.ini`, at `../libraries/MultiLegRobotWithIK/`. Editing
walking, IK, or special-pose behavior means editing files **outside the project directory**:

- `../libraries/MultiLegRobotWithIK/src/classes/RobotWithKinematics.h` — gait state machine, special-pose
  state machine, per-loop orchestration. The bulk of the interesting logic.
- `.../classes/RobotLeg.h` — per-leg geometry + the actual inverse kinematics (law of cosines) and
  per-step foot-target interpolation.
- `.../classes/{Vector3,LegAngles,BodyPose}.h` — value types.
- `.../src/basicFunctions.h` — `fmap`, `degToRad`, etc. (used by the project code too).

The repo's own `src/` is the **ESP32 firmware glue**: read RC input, call the engine, push results to servos.

## Architecture

`NUMBER_OF_LEGS` is a compile-time `#define` set in `src/Rocky_MK1.cpp` *before* `#include "system.h"`.
The library `static_assert`s it is ≥ 4 and sizes `std::array`s on it, so changing leg count is a recompile,
not a runtime config. `definitions.h` constructs the `RobotLeg myLegs[NUMBER_OF_LEGS]` array — each leg's
body-radius, segment lengths, foot extend, and **base angle around the body** are set there. Asymmetric
layouts work because every part of the engine reads each leg's `baseAngle` directly (no `i*360/N` assumption).

### Per-loop pipeline (`src/system.h::loop`)

1. `loopInput()` — `src/input.h` reads 10 IBUS channels into the `InputValues` struct (`input`). Sticks/pots
   are `fmap`'d to ranges; switches map to `Top/Middle/Bottom`. Failsafe falls back to neutral defaults.
2. `loopFootSensors()` — `src/footSensors.h` debounces 5 contact switches into `footOnGround[]` (currently
   read but not yet fed into the gait).
3. Map controls → `robot->applyControls(...)` (walk X/Y, body rotate, foot extend, height, tilt X/Z, yaw).
   `applyControls` only *commits* new targets at a clean cycle boundary (`currentPhase==0 && walkingStep==0`)
   so targets never change mid-step. Left-inside switch toggles **vehicle** vs **strafing** steering.
4. `robot->mainLoop()` — advances the gait state machine (`Walk_Idle/Active/Stopping`) and rotates which
   legs are currently lifted (`currentMovingLegs`).
5. `robot->prepareTargetPositions()` — computes each leg's foot target for this sub-step.
6. `robot->specialPoseLoop()` — special-pose state machine; overrides targets for the 1–2 legs involved in a
   choreographed gesture (triggered by `robot->doSpecialPose(n)` from the left-outside switch).
7. `robot->calculateAllLegAngles()` → `std::array<LegAngles>`; guarded by `robot->isValidPose()` (skips the
   write if any foot is unreachable, freezing the last good pose).
8. `moveAllLegs()` → `finalizeServoPositions()` — see servo layer below.

### Servo layer (`src/servoFunctions.h`)

The engine outputs joint angles in radians; this layer converts to ST3020 serial-servo digital positions and
writes them all at once via `st.SyncWritePosEx(...)`. Three things to know before touching it:

- **Logical leg/servo index ≠ physical servo ID.** `servoIds[]` in `definitions.h` remaps to the actual bus
  wiring; `servoNumber = leg*3 + servo`. Don't assume ID == index.
- **Per-servo trim** lives in `extraCalibrations.h` (`setupExtraCalibrations()`), added to every commanded
  angle. The hardware zero is `180°` (positions are offset around mid-range).
- **Tibia sign is inverted** in `moveOneLeg` (`-angles.tibiaDeg()`) — a mechanical convention, not a bug.

The `calibrate()` function and its `st.CalibrationOfs(...)` calls are commented out on purpose; uncommenting
them rewrites the servos' stored zero offsets (a one-time physical setup step), so leave them off for normal
operation.

## Gotchas

- Required external libs not vendored here: `workloads/SCServo`, `derdoktor667/FlyskyIBUS` (in
  `platformio.ini` `lib_deps`), plus the local `MultiLegRobotWithIK` via `lib_extra_dirs`.
- `Serial1` is the servo bus at 1 Mbaud on pins RX=18 / TX=19 (`system.h::setup`). `Serial` (USB) is logging.
- Foot-contact sensor pins: `{32, 33, 25, 26, 27}` (`footSensors.h`).
