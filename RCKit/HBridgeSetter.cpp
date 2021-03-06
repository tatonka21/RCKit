// HBridgeSetter.cpp
//
// Template for a CPP file
/// \author  Mike McCauley (mikem@airspayce.com)
///
// Copyright (C) 2010 Mike McCauley
// $Id: HBridgeSetter.cpp,v 1.4 2012/08/25 06:18:13 mikem Exp $

#include "HBridgeSetter.h"
#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

/////////////////////////////////////////////////////////////////////
HBridgeSetter::HBridgeSetter(Setter* targetA, Setter* targetB) : Setter(targetA)
{
    _targetB = targetB;
}

/////////////////////////////////////////////////////////////////////
void HBridgeSetter::setTargets(Setter* targetA, Setter* targetB)
{
    Setter::setTarget(targetA);
    _targetB = targetB;
}

/////////////////////////////////////////////////////////////////////
void HBridgeSetter::input(int value)
{
    // Output the value
    int outA, outB;
    if (value >= 127)
    {
	outA = (value - 127) << 1;
	outB = 0;
    }
    else // value < 127
    {
	outA = 0;
	outB = (127 - value) << 1;
    }
//    Serial.println("bridge");
//    Serial.println(outA, DEC);
//    Serial.println(outB, DEC);
    Setter::input(outA);
    if (_targetB)
	_targetB->input(outB);
}

/////////////////////////////////////////////////////////////////////
void HBridgeSetter::failsafe()
{
    Setter::failsafe();
    if (_targetB)
	_targetB->failsafe();
}

