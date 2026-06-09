/**
 * input.h
 *
 * Funktionen um Daten aus dem FlySky RC-Reciever auszulesen.
 *
 * Autor: Jeanette Müller
 * Datum: 2025
 */

#include "classes/InputValues.h"

// RC Reviever
#include <FlyskyIBUS.h>
FlyskyIBUS *IBus = new FlyskyIBUS();
uint16_t ibusVar00 = 0;
uint16_t ibusVar01 = 0;
uint16_t ibusVar02 = 0;
uint16_t ibusVar03 = 0;
uint16_t ibusVar04 = 0;
uint16_t ibusVar05 = 0;
uint16_t ibusVar06 = 0;
uint16_t ibusVar07 = 0;
uint16_t ibusVar08 = 0;
uint16_t ibusVar09 = 0;

#define RC_STICK_RIGHT_H (byte)0
#define RC_STICK_RIGHT_V (byte)1
#define RC_STICK_LEFT_V (byte)2
#define RC_STICK_LEFT_H (byte)3
#define RC_TURN_LEFT (byte)4
#define RC_TURN_RIGHT (byte)5
#define RC_SWITCH_LEFT_OUT (byte)6
#define RC_SWITCH_LEFT_IN (byte)7
#define RC_SWITCH_RIGHT_IN (byte)8
#define RC_SWITCH_RIGHT_OUT (byte)9

InputValues *input = new InputValues();

PositionSwitch getSwitchValueFrom(uint16_t val)
{
    if (val == 1000)
    {
        return Top;
    }
    else if (val == 1500)
    {
        return Middle;
    }
    else if (val == 2000)
    {
        return Bottom;
    }
    return Unknown;
}

void setDefaultValues()
{
    ibusVar00 = 1500;
    ibusVar01 = 1500;
    ibusVar02 = 1500;
    ibusVar03 = 1500;

    ibusVar04 = 1000;
    ibusVar05 = 1500;

    ibusVar06 = 1500;
    ibusVar07 = 1000;
    ibusVar08 = 1000;
    ibusVar09 = 1500;
}

void setupInput()
{
    IBus->begin();

    setDefaultValues();
}

void loopInput()
{
    ibusVar00 = IBus->getChannel(RC_STICK_RIGHT_H);    //
    ibusVar01 = IBus->getChannel(RC_STICK_RIGHT_V);    //
    ibusVar02 = IBus->getChannel(RC_STICK_LEFT_V);     //
    ibusVar03 = IBus->getChannel(RC_STICK_LEFT_H);     //
    ibusVar04 = IBus->getChannel(RC_TURN_LEFT);        // (drehregler links)
    ibusVar05 = IBus->getChannel(RC_TURN_RIGHT);       // (drehregler rechts)
    ibusVar06 = IBus->getChannel(RC_SWITCH_LEFT_OUT);  // (schalter links außen)
    ibusVar07 = IBus->getChannel(RC_SWITCH_LEFT_IN);   // (schalter links innen)
    ibusVar08 = IBus->getChannel(RC_SWITCH_RIGHT_IN);  // (schalter rechts innen)
    ibusVar09 = IBus->getChannel(RC_SWITCH_RIGHT_OUT); // (schalter rechts außen)

    // if (IBus->isFailsafe())
    // {
    //     Serial.println("FAILSAFE!");

    //     // setDefaultValues();
    // }

    input->failsafe = IBus->isFailsafe();

    if (input->failsafe)
    {
        setDefaultValues();
    }

    input->rightStickHorizontal = fmap(ibusVar00, 1000, 2000, -100.0, 100.0);
    input->rightStickVertical = fmap(ibusVar01, 1000, 2000, -100.0, 100.0);
    input->leftStickHorizontal = fmap(ibusVar03, 1000, 2000, -100.0, 100.0);
    input->leftStickVertical = fmap(ibusVar02, 1000, 2000, -100.0, 100.0);

    input->leftPoit = fmap(ibusVar04, 1000, 2000, 0.0, 1000.0);
    input->rightPoti = fmap(ibusVar05, 1000, 2000, 0.0, 1000.0);

    input->switchLeftOutside = getSwitchValueFrom(ibusVar06);
    input->switchLeftInside = getSwitchValueFrom(ibusVar07);
    input->switchRightInside = getSwitchValueFrom(ibusVar08);
    input->switchRightOutside = getSwitchValueFrom(ibusVar09);

    if (debug)
    {
        Serial.print("Input: ");

        Serial.print(" rightStick y: ");
        Serial.print(input->rightStickVertical);
        Serial.print(" x: ");
        Serial.print(input->rightStickHorizontal);

        Serial.print(" leftStick y: ");
        Serial.print(input->leftStickVertical);
        Serial.print(" x: ");
        Serial.print(input->leftStickHorizontal);

        Serial.print(" leftPoit: ");
        Serial.print(input->leftPoit);
        Serial.print(" rightPoti: ");
        Serial.print(input->rightPoti);

        Serial.print(" switches: ");
        Serial.print(" lo: ");
        Serial.print(input->switchLeftOutside);
        Serial.print(" li: ");
        Serial.print(input->switchLeftInside);
        Serial.print(" ri: ");
        Serial.print(input->switchRightInside);
        Serial.print(" lr: ");
        Serial.println(input->switchRightOutside);
    }

    if (input->failsafe)
    {
        // Serial.print(" -- is failsafe: ");
        // Serial.println(input->failsafe ? "true" : "false");
    }
}
