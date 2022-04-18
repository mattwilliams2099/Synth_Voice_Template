/*
  ==============================================================================

    Voice.h
    Created: 12 Apr 2022 2:12:07pm
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "ADSR.h"
#include "Filter.h"
class VoiceClass
{
private:
    OscillatorClass oscillator { sampleRate };
    ADSRClass ampEnvelope { sampleRate };
    FilterClass LPF { sampleRate };
    float midiNoteToHz(int midiNote);
    float sampleRate;
public:
    VoiceClass (float samplerate);
    VoiceClass() = default;
    float voiceProcess();
    void newNote(int midiNote);
    void noteRelease();
    bool isPlaying();
    void setSampleRate(float newValue);
    void prepareToPlay();

};
