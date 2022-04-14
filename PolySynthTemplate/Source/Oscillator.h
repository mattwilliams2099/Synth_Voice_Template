/*
  ==============================================================================

    Oscillator.h
    Created: 12 Apr 2022 2:34:05pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#define WAVETABLE_LENGTH 64
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


class OscillatorClass
{
private:
    float wavetable[WAVETABLE_LENGTH];
    void fillWavetable();

    float sampleRate;
    float index = 0.0f;
    float indexIncrement = 0.0f;
    float linearInterpolate();

public:
    OscillatorClass(float samplerate);
    OscillatorClass() = default;
    float oscillatorProcess();
    void setFrequency(float frequency);
    void setSampleRate(float newValue) { sampleRate = newValue; }
    void stop();
    bool isPlaying();

};