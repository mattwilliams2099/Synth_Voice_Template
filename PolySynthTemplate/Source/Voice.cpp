/*
  ==============================================================================

    Voice.cpp
    Created: 12 Apr 2022 2:12:07pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Voice.h"

VoiceClass::VoiceClass (float samplerate) : sampleRate(samplerate)
{
    //sampleRate = samplerate;

}

float VoiceClass::voiceProcess()
{
    float oscOutput = oscillator[0].oscillatorProcess() + oscillator[1].oscillatorProcess() + oscillator[2].oscillatorProcess();
    float filterOutput = LPF.filterProcess((oscOutput * 0.3), 0);
    float ampOutput = filterOutput * ampEnvelope.ADSRProcess();
    return ampOutput;
}

void VoiceClass::newNote (int midiNote)
{
    auto frequencyHz = midiNoteToHz(midiNote);
    oscillator[0].setFrequency(frequencyHz);
    oscillator[1].setFrequency(frequencyHz);
    oscillator[2].setFrequency(frequencyHz);
    ampEnvelope.keyDown();
}

float VoiceClass::midiNoteToHz (int midiNote)
{
    return 400.0f * std::powf (2.0f, (midiNote - 69.0f) / 12.0f);
}

void VoiceClass::noteRelease()
{
    ampEnvelope.keyUp();
}

bool VoiceClass::isPlaying()
{
    return ampEnvelope.isActive();
}

void VoiceClass::prepareToPlay()
{

}

void VoiceClass::setSampleRate(float newValue) 
{ 
    sampleRate = newValue; 
    oscillator[0].setSampleRate (sampleRate); 
    oscillator[1].setSampleRate(sampleRate);
    oscillator[2].setSampleRate(sampleRate);
    ampEnvelope.setSampleRate (sampleRate); 
    LPF.setSampleRate (sampleRate);
}


