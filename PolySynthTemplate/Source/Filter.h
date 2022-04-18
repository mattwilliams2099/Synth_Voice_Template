/*
  ==============================================================================

    FilterClass.h
    Created: 19 Jan 2022 1:43:44pm
    Author:  mwill

  ==============================================================================
*/

#pragma once
#define _USE_MATH_DEFINES
#include <cmath>

//#define pi 3.14159265
class FilterClass
{
private:
    float b[3] = { 0.0f, 0.0f, 0.0f };
    float a[3] = { 0.0f, 0.0f, 0.0f };
    float xz[2][2] = { { 0.0f, 0.0f }, {0.0f, 0.0f} };
    float yz[2][2] = { { 0.0f, 0.0f }, {0.0f, 0.0f} };
    float sampleRate;
    float cutoff;
    float resonance;

public:
    FilterClass(float sampleFreq = 48000);
    float filterProcess(float x, int channel);
    void setLowPassCo(float cutoff, float q = 0.5);
    void setBandPassCo(float cutoff, float q = 0.5);
    void setHighPassCo(float cutoff, float q = 0.5);
    void setSampleRate(float newValue) { sampleRate = newValue; }
};
