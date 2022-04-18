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
        if (attackStage == true)
        {
            output += attackIncrement;
            if (output >= 1.0f)
            {
                output = 1;
                attackStage = false;
                decayStage = true;
            }
        }
        else if (decayStage == true)
        {
            output -= decayIncrement;
            if (output <= sustain)
            {
                output = sustain;
                decayStage = false;
                sustainStage = true;
            }
        }
        else if (sustainStage == true)
            output = sustain;
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

void ADSRClass::setDecay(int newDecay)
{

    decay = millisecondsToSamples(static_cast<float>(newDecay));
    decayIncrement = (1.0f - sustain) / static_cast<float>(decay);
}

void ADSRClass::setSustain(float newSustain)
{
    sustain = newSustain;
    decayIncrement = (1.0f - sustain) / static_cast<float>(decay);
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
    attackStage = true;
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