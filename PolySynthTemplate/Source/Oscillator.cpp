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
    fillWavetable();
}

void OscillatorClass::fillWavetable()
{
    for (int i = 0; i < WAVETABLE_LENGTH; i++)
    {
        wavetable[i] = sin((2 * M_PI * static_cast<float>(i)) / static_cast<float>(WAVETABLE_LENGTH));
    }
}

void OscillatorClass::setFrequency(float frequency)
{
    indexIncrement = frequency * static_cast<float>(WAVETABLE_LENGTH) / sampleRate;
}

float OscillatorClass::oscillatorProcess()
{
    float sample = linearInterpolate();
    index += indexIncrement;
    index = std::fmod(index, static_cast<float>(WAVETABLE_LENGTH));

}

float OscillatorClass::linearInterpolate()
{
    const auto truncatedIndex = static_cast<int>(index);
    const auto nextIndex = (truncatedIndex + 1) % static_cast<int>(WAVETABLE_LENGTH);
    const auto nextIndexWeight = index - static_cast<float>(truncatedIndex);
    const auto truncatedIndexWeight = 1.0f - nextIndexWeight;

    return truncatedIndexWeight * wavetable[truncatedIndex] + nextIndexWeight * wavetable[nextIndex];
}