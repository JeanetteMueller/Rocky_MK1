/**
 * definitions.h
 *
 * Basis Variablen
 *
 * Autor: Jeanette Müller
 * Datum: 2025
 */

bool debug = false;

SMS_STS st;

#define SERVO_NUM (NUMBER_OF_LEGS * 3) // Number of servos
// u8 servoIds[SERVO_NUM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
u8 servoIds[SERVO_NUM] = {5, 14, 15, 7, 8, 9, 4, 2, 3, 10, 11, 6, 13, 1, 12};
s16 newPosition[SERVO_NUM];
u16 newSpeed[SERVO_NUM];
u8 newAcc[SERVO_NUM];

const u16 speed = 4000;
const u8 acc = 0;

bool calibrated = false;

#include "../extraCalibrations.h"

// Timing
const uint16_t walkingStepCount = 60;
const uint16_t mainLoopDelay = 5;

// Sizes
const float bodyCenterToLegsCircleRadius = 104.175; // mm
const float coxaLength = 54.0;                      // mm
const float thighLength = 120.0;                    // mm
const float shinLength = 217.0 + 5.5;               // mm // shin + rubber pad
const float minStepHeight = 30.0;
const float centerOfMassShiftFactor = 0.4; // 0.0 = off, 1.0 = all the way to centroid

// Joint limits for Rocky (in degrees). These values used to be hard-coded in
// the library (LegAngles.h) and are now configured centrally here.
//                      { min,    max }
const LegLimits rockyLegLimits = {
    {-65.0, 65.0},   // coxa  (swing)
    {-130.0, 130.0}, // femur (lift)
    {-140.0, 140.0}  // tibia (knee)  = ±(180 - 40)
};

// Position
const float startBodyHeightOverGround = 160.0;            // mm
const float startLegExtend = 280.0;                       // mm
const float heightOffset = 0.0;

// Min/Max Values
const float maxTilt = 26.0;
const float maxRotation = 30.0;
const float maxStepWidth = 230.0;
const float minHeight = 170.0; // mm
const float maxHeight = 285.0; // mm
const float maxRotationBodyOnPoint = 260.0; // mm

// Offset
AxisOffset legAxisOffset = {0.0f, 0.0f};

// Conditions
const bool enableCenterOfMassShift = false;
bool multiLegMovement = true;

// Robot itself
RobotWithKinematics *robot;

// Legs
static RobotLeg myLegs[NUMBER_OF_LEGS] = {
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        minStepHeight,                // min height of foot over ground when walking
        0,                            // degree of first servo from front of robot
        -2.0f * 0,
        rockyLegLimits,               // joint limits
        legAxisOffset                 // Lateral axial displacement of the knee {femur, tibia} in mm
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        minStepHeight,                // min height of foot over ground when walking
        72,                           // degree of first servo from front of robot
        -2.0f * 72,
        rockyLegLimits,               // joint limits
        legAxisOffset                 // Lateral axial displacement of the knee {femur, tibia} in mm
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        minStepHeight,                // min height of foot over ground when walking
        144,                          // degree of first servo from front of robot
        -2.0f * 144,
        rockyLegLimits,               // joint limits
        legAxisOffset                 // Lateral axial displacement of the knee {femur, tibia} in mm
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        minStepHeight,                // min height of foot over ground when walking
        216,                          // degree of first servo from front of robot
        -2.0f * 216,
        rockyLegLimits,               // joint limits
        legAxisOffset                 // Lateral axial displacement of the knee {femur, tibia} in mm
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        minStepHeight,                // min height of foot over ground when walking
        288,                          // degree of first servo from front of robot
        -2.0f * 288,
        rockyLegLimits,               // joint limits
        legAxisOffset                 // Lateral axial displacement of the knee {femur, tibia} in mm
        )};
