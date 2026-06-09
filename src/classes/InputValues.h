/**
 * InputValues.h
 *
 * C++ Klasse um eingaben von der FlySky RC-Remote anzunehmen.
 *
 * Autor: Jeanette Müller
 * Datum: 2025
 */

#ifndef InputValues_h
#define InputValues_h

enum PositionSwitch
{
    Top,
    Middle,
    Bottom,
    Unknown
};

class InputValues
{
public:
    InputValues() {};
    float rightStickHorizontal;
    float rightStickVertical;
    float leftStickHorizontal;
    float leftStickVertical;
    float leftPoit;
    float rightPoti;

    PositionSwitch switchLeftOutside;
    PositionSwitch switchLeftInside;
    PositionSwitch switchRightOutside;
    PositionSwitch switchRightInside;

    bool failsafe;

private:
};

#endif