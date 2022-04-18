/*
  ==============================================================================

    FilterClass.cpp
    Created: 19 Jan 2022 1:43:44pm
    Author:  mwill

  ==============================================================================
*/

#include "Filter.h"


FilterClass::FilterClass(float sampleFreq)
{
    sampleRate = sampleFreq;
}


float FilterClass::filterProcess(float x, int channel)
{
    float y = (b[0] * x) + (b[1] * xz[0][channel]) + (b[2] * xz[1][channel]) - (a[1] * yz[0][channel]) - (a[2] * yz[1][channel]);
    xz[1][channel] = xz[0][channel];
    xz[0][channel] = x;
    yz[1][channel] = yz[0][channel];
    yz[0][channel] = y;
    return y;
}

void FilterClass::setLowPassCo(float cutoff, float q)
{
    float omega = 2 * M_PI * (cutoff / sampleRate);
    float alpha = sin(omega) / (2 * q);

    b[0] = (1 - cos(omega)) / 2;
    b[1] = 1 - cos(omega);
    b[2] = (1 - cos(omega)) / 2;
    a[0] = 1 + alpha;
    a[1] = (-2) * cos(omega);
    a[2] = 1 - alpha;

    b[0] = b[0] / a[0];
    b[1] = b[1] / a[0];
    b[2] = b[2] / a[0];
    a[1] = a[1] / a[0];
    a[2] = a[2] / a[0];
    a[0] = a[0] / a[0];
}

void FilterClass::setHighPassCo(float cutoff, float q)
{
    float omega = 2 * M_PI * (cutoff / sampleRate);
    float alpha = sin(omega) / (2 * q);

    b[0] = (1 + cos(omega)) / 2;
    b[1] = -(1 + cos(omega));
    b[2] = (1 + cos(omega)) / 2;
    a[0] = 1 + alpha;
    a[1] = (-2) * cos(omega);
    a[2] = 1 - alpha;

    b[0] = b[0] / a[0];
    b[1] = b[1] / a[0];
    b[2] = b[2] / a[0];
    a[1] = a[1] / a[0];
    a[2] = a[2] / a[0];
    a[0] = a[0] / a[0];
}

void FilterClass::setBandPassCo(float cutoff, float q)
{
    float omega = 2 * M_PI * (cutoff / sampleRate);
    float alpha = sin(omega) / (2 * q);

    b[0] = alpha;
    b[1] = 0;
    b[2] = -alpha;
    a[0] = 1 + alpha;
    a[1] = (-2) * cos(omega);
    a[2] = 1 - alpha;

    b[0] = b[0] / a[0];
    b[1] = b[1] / a[0];
    b[2] = b[2] / a[0];
    a[1] = a[1] / a[0];
    a[2] = a[2] / a[0];
    a[0] = a[0] / a[0];
}


