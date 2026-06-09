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

const float bodyCenterToLegsCircleRadius = 104.175; // mm
const float coxaLength = 54.0;                      // mm
const float thighLength = 120.0;                    // mm
const float shinLength = 217.0 + 5.5;               // mm // shin + rubber pad
float startBodyHeightOverGround = 160.0;            // mm
float startLegExtend = 170.0;                       // mm
float heightOffset = 0.0;

RobotWithKinematics *robot;
static RobotLeg myLegs[NUMBER_OF_LEGS] = {
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        0                             // degree of first servo from front of robot
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        72                            // degree of first servo from front of robot
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        144                           // degree of first servo from front of robot
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        216                           // degree of first servo from front of robot
        ),
    RobotLeg(
        bodyCenterToLegsCircleRadius, // body radius in mm
        coxaLength,                   // coxa length in mm
        thighLength,                  // thigh length in mm
        shinLength,                   // shin length in mm
        heightOffset,                 // offset from center of mass
        startLegExtend,               // distance of first servo axis to foot
        288                           // degree of first servo from front of robot
        )};

const uint16_t walkingStepCount = 70;
const uint16_t mainLoopDelay = 5;
const float maxTilt = 26.0;
const float maxRotation = 30.0;
const float maxStepWidth = 230.0;

const float minHeight = 170.0; // mm
const float maxHeight = 285.0; // mm

const float maxRotationBodyOnPoint = 260.0; // mm

float waveLegA = 0;
bool waveLegADirection = true;