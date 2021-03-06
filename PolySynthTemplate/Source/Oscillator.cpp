/*
  ==============================================================================

    Oscillator.cpp
    Created: 12 Apr 2022 2:34:05pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Oscillator.h"

OscillatorClass::OscillatorClass(float samplerate) : sampleRate(samplerate)
{
    //fillWavetable(square);
}

void OscillatorClass::fillWavetable(int shape)
{
    std::fill_n(wavetable, WAVETABLE_LENGTH, 0.0f);
    //const float sawIncrement = 2.0f / static_cast<float>(WAVETABLE_LENGTH);
    //float sawCounter = -1.0f;
    //float triIncrement = 4.0f / static_cast<float>(WAVETABLE_LENGTH);
    //float triCounter = 0.0f;
    float increment;
    float counter = 0.0f;
    switch (shape)
    {
    case 0: //Sine
        for (int i = 0; i < WAVETABLE_LENGTH; i++)
        {
            wavetable[i] = sin((2 * M_PI * static_cast<float>(i)) / static_cast<float>(WAVETABLE_LENGTH));
        }
        break;
    
    case 1: //Saw
        counter = -1.0f;
        increment = 2.0f / static_cast<float>(WAVETABLE_LENGTH);
        for (int i = 0; i < WAVETABLE_LENGTH; i++)
        {
            counter += increment;
            wavetable[i] = counter;
        }
        break;

    case 2: //Triangle
        increment = 4.0f / static_cast<float>(WAVETABLE_LENGTH);
        for (int i = 0; i < WAVETABLE_LENGTH; i++)
        {
            if (i == WAVETABLE_LENGTH / 4 || i == (WAVETABLE_LENGTH / 4) * 3)
                increment = (-increment);
            counter += increment;
            wavetable[i] = counter;
        }
        break;

    case 3: //Square
        for (int i = 0; i < WAVETABLE_LENGTH; i++)
        {
            if (i < WAVETABLE_LENGTH / 2)
                wavetable[i] = 1.0f;
            else
                wavetable[i] = -1.0f;
        }
        break;
    }
}

void OscillatorClass::setFrequency(float newFrequency)
{
    frequency = newFrequency;
    indexIncrement = (fineFreq * coarseFreq * frequency) * static_cast<float>(WAVETABLE_LENGTH) / sampleRate;
}

float OscillatorClass::oscillatorProcess()
{
    float sample = linearInterpolate();
    index += indexIncrement;
    index = std::fmod(index, static_cast<float>(WAVETABLE_LENGTH));
    return sample;
}

float OscillatorClass::linearInterpolate()
{
    const auto truncatedIndex = static_cast<int>(index);
    const auto nextIndex = (truncatedIndex + 1) % static_cast<int>(WAVETABLE_LENGTH);
    const auto nextIndexWeight = index - static_cast<float>(truncatedIndex);
    const auto truncatedIndexWeight = 1.0f - nextIndexWeight;

    return truncatedIndexWeight * wavetable[truncatedIndex] + nextIndexWeight * wavetable[nextIndex];
}

void OscillatorClass::stop()
{
    index = 0;
    indexIncrement = 0;
}

bool OscillatorClass::isPlaying()
{
    return indexIncrement != 0;
}
