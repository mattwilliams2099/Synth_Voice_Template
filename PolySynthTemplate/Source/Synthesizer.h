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
    
    VoiceClass voices{ sampleRate };
    float sampleRate;
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
public:
    SynthesizerClass(float samplerate);
    SynthesizerClass() = default;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void prepareToPlay(double samplerate);



};