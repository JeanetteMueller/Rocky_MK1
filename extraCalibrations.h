

std::array<LegAngles, NUMBER_OF_LEGS> extraCalibrations;

void setupExtraCalibrations()
{
    for (uint8_t i = 0; i < NUMBER_OF_LEGS; i++)
    {
        extraCalibrations[i] = LegAngles();
    }

    extraCalibrations[0].coxa = degToRad(0);
    extraCalibrations[1].coxa = degToRad(0);
    extraCalibrations[2].coxa = degToRad(0);
    extraCalibrations[3].coxa = degToRad(0);
    extraCalibrations[4].coxa = degToRad(0);

    // positiv ist hoch
    extraCalibrations[0].femur = degToRad(0);
    extraCalibrations[1].femur = degToRad(0);
    extraCalibrations[2].femur = degToRad(0);
    extraCalibrations[3].femur = degToRad(0);
    extraCalibrations[4].femur = degToRad(0);

    // positiv ist nach außen/hoch
    extraCalibrations[0].tibia = degToRad(0);
    extraCalibrations[1].tibia = degToRad(0);
    extraCalibrations[2].tibia = degToRad(0);
    extraCalibrations[3].tibia = degToRad(0);
    extraCalibrations[4].tibia = degToRad(0);
}