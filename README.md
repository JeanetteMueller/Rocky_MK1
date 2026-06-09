# Multi-leg Robot with Inverse Kinematics

A DIY walking robot with a configurable number of legs, fully 3D-printed and powered by an ESP32 microcontroller.

Have a look at

[![Instagram Post](./images/instagram_photo_1.png)](https://www.instagram.com/reel/DXeBLnWDbUL/?igsh=MTJqa2dneTdlbXB5dA==)

## What is This?

This is a multi-legged walking robot designed to support **any leg count and any leg layout** you can imagine. Each leg is its own configurable object — its position around the body, its orientation, and its segment lengths can all be set individually. That means you are not limited to a symmetric pentapod or a classic hexapod: you can build a four-legged scout, a perfectly symmetric octopod, or something deliberately asymmetric with longer front legs, shorter back legs, or unusual angular spacing.

Every leg has three joints driven by three servo motors — Coxa (hip swing), Femur (hip lift), and Tibia (knee). All legs are coordinated so the robot can walk, turn, and perform gestures.

## Asymmetric Robots Are a First-Class Feature

The legs are no longer assumed to be evenly distributed. When constructing the robot, you pass in an array of `RobotLeg` objects, and each one gets its own parameters:

```cpp
static RobotLeg myLegs[NUMBER_OF_LEGS] = {
    RobotLeg(bodyRadius, coxaLength, femurLength, tibiaLength,
             baseFootExtend,     // distance from first servo axis to foot
             baseAngleDeg,       // where this leg sits on the body (degrees)
             rotationOffset),    // how the leg is mounted (degrees)
    // ... one entry per leg, each fully independent
};
```

This unlocks designs like:

- **Spider-style asymmetry:** longer reach in front, shorter rear legs
- **Custom layouts:** legs clustered on one side, or grouped in pairs
- **Mixed geometries:** different femur/tibia lengths per leg for specialized roles
- **Non-uniform spacing:** legs at any angle around the body, not just `360° / N`

The inverse kinematics, gait planning, and special-pose system all read each leg's parameters directly, so an asymmetric build behaves correctly without any special-case code.

## Design

**Body:** Round body with the legs arranged around the perimeter. In the default five-legged build, the body has a radius of approximately 104 mm (center to leg attachment point) and the legs are placed at 72° intervals — but neither the count nor the spacing is hard-wired into the math.

**Legs:** Each leg has three segments:

- **Coxa** — 54 mm, the short hip segment that swings the leg sideways
- **Femur** — 120 mm, the upper leg segment lifted by the second servo
- **Tibia** — 222.5 mm (217 mm shin + 5.5 mm rubber foot pad), the lower leg segment moved by the knee

**Brain:** An ESP32 microcontroller handles all motion calculations, drives the servos via a serial bus, and reads input from the remote control receiver.

**Shell:** All structural parts are 3D-printed.

## How Does It Move?

The robot uses **inverse kinematics** — instead of manually setting angles for each servo, you define where a foot should be in 3D space, and the required joint angles are calculated automatically using trigonometry (law of cosines). This keeps the feet planted on the ground even when the body height, tilt, or yaw changes.

When walking, the robot lifts one or two legs at a time while the remaining legs support the body and push it forward. At low speed, only one leg lifts per phase (more stable). At higher speed, two legs lift simultaneously (faster but less stable). The gait runs as a cyclic phase pattern that adapts automatically to the number of legs in the configuration.

In addition to walking, the robot supports **special poses** — predefined choreographed movements where a pair of legs leaves the gait cycle, moves into a custom position, holds it, and returns to the standing pose. This is used for waving, greeting gestures, or any other interactive behavior.

## Controls

The robot uses a **FlySky receiver (10 channel)** to connect to a FlySky transmitter. All inputs are transmitted to the ESP32 in real time over the IBUS protocol.

Inputs include:

- **Right stick:** walk direction and speed (or steering, depending on mode)
- **Left stick:** body tilt (pitch and roll)
- **Left potentiometer:** body height
- **Right potentiometer:** body yaw rotation
- **Switches:** mode switch (vehicle vs. strafing), special poses, gesture triggers

A switch on the transmitter toggles between two control schemes:

- **Vehicle mode:** forward/backward + steering, like a car
- **Strafing mode:** full directional control, like a tank or RC drone

## Specs

| | |
|---|---|
| **Legs** | Configurable (default build: 5) |
| **Servos per leg** | 3 (Coxa, Femur, Tibia) |
| **Microcontroller** | ESP32 |
| **Coxa length** | 54 mm |
| **Femur length** | 120 mm (default, per-leg configurable) |
| **Tibia length** | 222.5 mm (default, per-leg configurable) |
| **Body radius** | ~104 mm (default, center to leg attachment) |
| **Body height range** | 170–285 mm |
| **Max step width** | 230 mm |
| **Max body tilt** | ±20° |
| **Max body rotation (yaw)** | ±25° |
| **Communication** | FlySky receiver (IBUS) |
| **Servo bus** | Serial (SCServo) |
| **Shell** | 3D-printed |
| **Kinematics** | Inverse kinematics (law of cosines) |
| **Language** | C++ (Arduino framework) |

## Future Plans

- **Sensors:** IMU for automatic body leveling on uneven terrain, foot contact sensors for adaptive gait
- **Reinforcement learning:** Training an AI-driven gait, first in simulation (MuJoCo / PyBullet), then transferring to the real robot
- **Range sensor:** Front-facing ToF sensor for obstacle detection

## Build Notes

### Stuff to Buy

- 3 × leg-count ST3020 serial servos (15 for the default 5-leg build)
- Serial servo controller board
- ESP32 dev board
- FlySky 6/10 channel transmitter + receiver

### 3D Printing

Inside the STL folder you will find files for 3D printing. The end of each filename indicates how many copies to print — for example, a file ending in `x5` needs to be printed five times.

### Prepare the Servos

Use my programmer to assign the servo IDs (1 to N):
[https://github.com/JeanetteMueller/SerialServoIdProgrammer](https://github.com/JeanetteMueller/SerialServoIdProgrammer)

### Required Libraries

- [FlyskyIBUS](https://github.com/derdoktor667/FlyskyIBUS)
- [SCServo](https://github.com/workloads/scservo)

## License & Contact

This is a personal hobby project.
