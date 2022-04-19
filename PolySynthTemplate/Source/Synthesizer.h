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
    
    VoiceClass voices{ sampleRate };
    float sampleRate;
    void handleMidiEvent(const juce::MidiMessage& midiEvent);
    void render(juce::AudioBuffer<float>& buffer, int startSample, int endSample);
    int activeNoteID[NUM_VOICES] = { 0, 0 };
public:
    SynthesizerClass(float samplerate);
    SynthesizerClass() = default;
    void processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages);
    void prepareToPlay(double samplerate);

    void setOscShape(int newValue, int oscNumber) 
    { 
        //for(VoiceClass voice : voices)
            voices.setOscShape (newValue, oscNumber); 
    }

    void setOscFineFreq(float newValue, int oscNumber)
    {
        voices.setOscFine(newValue, oscNumber);
    }

    void setOscCoarseFreq(float newValue, int oscNumber)
    {
        voices.setOscCoarse(newValue, oscNumber);
    }

    void setFilter(float newCutoff, float newResonance) 
    { 
        //for (VoiceClass voice : voices)
            voices.setFilter(newCutoff, newResonance); 
    }
    
    void setAmpAttack(int newValue) 
    {
        //for (VoiceClass voice : voices)
            voices.setAmpAttack(newValue); 
    }

    void setAmpDecay(int newValue) 
    {
        //for (VoiceClass voice : voices)
            voices.setAmpDecay(newValue); 
    }

    void setAmpSustain(float newValue) 
    {
        //for (VoiceClass voice : voices)
            voices.setAmpSustain(newValue); 
    }

    void setAmpRelease(int newValue) 
    {
        //for (VoiceClass voice : voices)
            voices.setAmpRelease(newValue); 
    }

};