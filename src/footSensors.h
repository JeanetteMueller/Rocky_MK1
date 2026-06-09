/**
 * footSensors.h
 *
 * Fuß-Bodenkontakt-Taster (schließend, gegen GND, INPUT_PULLUP).
 */

#ifndef FOOT_SENSORS_H
#define FOOT_SENSORS_H

const uint8_t footSensorPins[NUMBER_OF_LEGS] = {32, 33, 25, 26, 27};

// gefilterte Zustände
bool footOnGround[NUMBER_OF_LEGS] = {false, false, false, false, false};

// Entprellung
uint8_t footDebounceCounter[NUMBER_OF_LEGS] = {0};
constexpr uint8_t FOOT_DEBOUNCE_THRESHOLD = 3; // Loops

void setupFootSensors()
{
    for (uint8_t i = 0; i < NUMBER_OF_LEGS; i++)
    {
        pinMode(footSensorPins[i], INPUT_PULLUP);
    }
}

void loopFootSensors()
{
    for (uint8_t i = 0; i < NUMBER_OF_LEGS; i++)
    {
        // Taster schließend gegen GND -> LOW = gedrückt = Bodenkontakt
        bool raw = (digitalRead(footSensorPins[i]) == LOW);

        if (raw == footOnGround[i])
        {
            footDebounceCounter[i] = 0;
        }
        else
        {
            footDebounceCounter[i]++;
            if (footDebounceCounter[i] >= FOOT_DEBOUNCE_THRESHOLD)
            {
                footOnGround[i] = raw;
                footDebounceCounter[i] = 0;
            }
        }
    }
}

#endif