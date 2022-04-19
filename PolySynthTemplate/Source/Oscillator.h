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
    float fineFreq = 1.0f;
    float coarseFreq = 1.0f;
    float frequency;
    float sampleRate;
    float index = 0.0f;
    float indexIncrement = 0.0f;
    float linearInterpolate();
    void fillWavetable (int shape);
public:    
    OscillatorClass (float samplerate = 44100.0f);
    //OscillatorClass() = default;
    float oscillatorProcess();
    void setFrequency (float newFrequency);
    void setSampleRate (float newValue)     { sampleRate = newValue; }
    void setWaveShape (int waveShape)       { fillWavetable(waveShape); }    
    void setFineFreq(float newFineFreq) { fineFreq = newFineFreq; setFrequency(frequency); }
    void setCoarseFreq (float newCoarseFreq) { coarseFreq = newCoarseFreq; setFrequency(frequency); }
    void stop();
    bool isPlaying();


};