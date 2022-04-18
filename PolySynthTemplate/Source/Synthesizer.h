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

#define NUM_VOICES 2
class SynthesizerClass
{
private:
    
    VoiceClass voices[NUM_VOICES]{ sampleRate };
    float sampleRate;
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
    int activeNoteID[NUM_VOICES] = { 0, 0 };
public:
    SynthesizerClass(float samplerate);
    SynthesizerClass() = default;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void prepareToPlay(double samplerate);

    void setOsc1Shape(int newValue) 
    { 
        for(VoiceClass voice : voices)
            voice.setOsc1Shape (newValue); 
    }

    void setFilter(float newCutoff, float newResonance) 
    { 
        for (VoiceClass voice : voices)
            voice.setFilter(newCutoff, newResonance); 
    }
    
    void setAmpAttack(int newValue) 
    {
        for (VoiceClass voice : voices)
            voice.setAmpAttack(newValue); 
    }

    void setAmpDecay(int newValue) 
    {
        for (VoiceClass voice : voices)
            voice.setAmpDecay(newValue); 
    }

    void setAmpSustain(float newValue) 
    {
        for (VoiceClass voice : voices)
            voice.setAmpSustain(newValue); 
    }

    void setAmpRelease(int newValue) 
    {
        for (VoiceClass voice : voices)
            voice.setAmpRelease(newValue); 
    }

};