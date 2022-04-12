/*
  ==============================================================================

    Synthesizer.h
    Created: 12 Apr 2022 2:11:55pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "Voice.h"
class SynthesizerClass
{
private:
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    VoiceClass voices[8];


public:




};