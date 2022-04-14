/*
  ==============================================================================

    ADSR.cpp
    Created: 13 Apr 2022 5:55:26pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "ADSR.h"


ADSRClass::ADSRClass(float samplerate) : sampleRate(samplerate)
{

}

float ADSRClass::ADSRProcess()
{
    if (gate == true)
    {        
        if (output < 1)
            output += attackIncrement;    
    }
    else if (gate == false)
    {
        if (output > 0)
            output -= releaseIncrement;
    }
    return output;
}

void ADSRClass::setAttack(int newAttack)
{
    attack = millisecondsToSamples(static_cast<float>(newAttack));
    attackIncrement = 1.0f / static_cast<float>(attack);
}

void ADSRClass::setRelease(int newRelease)
{
    release = millisecondsToSamples(static_cast<float>(newRelease));
}

float ADSRClass::millisecondsToSamples(float milliseconds)
{
    return milliseconds * (sampleRate / 1000.0f);
}

void ADSRClass::keyDown()
{
    gate = true;
}

void ADSRClass::keyUp()
{
    gate = false;
    releaseIncrement = output / static_cast<float>(release);

}

bool ADSRClass::isActive()
{
    return output != 0.0f || gate == true;

}