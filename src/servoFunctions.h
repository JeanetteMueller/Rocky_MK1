/**
 * servoFunctions.h
 *
 * Basis funktionen um mit den ST3020 Servos zu arbeiten.
 *
 * Autor: Jeanette Müller
 * Datum: 2025
 */

float ServoDigitalRange_ST = 4095.0;
float ServoAngleRange_ST = 360.0;
float ServoInitACC_ST = 2000;
float ServoMaxSpeed_ST = 4000;
float ServoMaxACC_ST = 100;

s16 calcSerialServoDegree(float degree)
{
  return fmap(degree, 0.0, ServoAngleRange_ST, 0.0, ServoDigitalRange_ST);
}

void initServoPositions()
{
  u16 speed = 2000;
  u8 acc = 0;
  s16 pos = calcSerialServoDegree(180);

  for (uint8_t i = 0; i < SERVO_NUM; i++)
  {
    newPosition[i] = pos;
    newSpeed[i] = speed;
    newAcc[i] = acc;
  }
}

void setDegreeForLegAndServo(uint8_t leg, uint8_t servo, float degree, u16 speed, u8 acc)
{
  uint8_t servoNumber = leg * 3 + servo;

  float target = 180 + degree;

  if (target >= 360)
  {
    target = target - 360;
  }
  else if (target <= -360)
  {
    target = target + 360;
  }

  newPosition[servoNumber] = calcSerialServoDegree(target);
  newSpeed[servoNumber] = speed;
  newAcc[servoNumber] = acc;
}

void finalizeServoPositions()
{
  st.SyncWritePosEx(servoIds, SERVO_NUM, newPosition, newSpeed, newAcc);
}

void calibrate()
{
  Serial.print("Calibrate Servos...");

  delay(1000);

  //// Bein 0 (front)
  // st.CalibrationOfs(5);
  // st.CalibrationOfs(14);
  // st.CalibrationOfs(15);

  // //// Bein 1
  // st.CalibrationOfs(7);
  // st.CalibrationOfs(8);
  // st.CalibrationOfs(9);

  // //// Bein 2
  // st.CalibrationOfs(4);
  // st.CalibrationOfs(2);
  // st.CalibrationOfs(3);

  // //// Bein 3
  // st.CalibrationOfs(10);
  // st.CalibrationOfs(11);
  // st.CalibrationOfs(6);

  // //// Bein 4
  // st.CalibrationOfs(13);
  // st.CalibrationOfs(1);
  // st.CalibrationOfs(12);

  Serial.println(" done");
  delay(500);
}

void moveOneLeg(uint8_t legIndex, LegAngles angles, bool finalize)
{
  // Serial.print("moveOneLeg: ");
  // Serial.println(legIndex);

  LegAngles calibration = extraCalibrations[legIndex];

  setDegreeForLegAndServo(legIndex, 0, calibration.coxaDeg() + angles.coxaDeg(), speed, acc);
  setDegreeForLegAndServo(legIndex, 1, calibration.femurDeg() + angles.femurDeg(), speed, acc);
  setDegreeForLegAndServo(legIndex, 2, calibration.tibiaDeg() + -angles.tibiaDeg(), speed, acc);

  if (finalize)
  {
    u8 singleServoIds[3] = {servoIds[legIndex * 3], servoIds[legIndex * 3 + 1], servoIds[legIndex * 3 + 2]};

    s16 singlePosition[3] = {newPosition[legIndex * 3], newPosition[legIndex * 3 + 1], newPosition[legIndex * 3 + 2]};
    u16 singleSpeed[3] = {3000, 3000, 3000};
    u8 singleAcc[3] = {0, 0, 0};

    st.SyncWritePosEx(singleServoIds, 3, singlePosition, singleSpeed, singleAcc);
  }
}

void moveAllLegs(std::array<LegAngles, NUMBER_OF_LEGS> allAngles)
{
  for (uint8_t legIndex = 0; legIndex < NUMBER_OF_LEGS; legIndex++)
  {
    LegAngles angles = allAngles[legIndex];
    moveOneLeg(legIndex, angles, false);
  }
}
