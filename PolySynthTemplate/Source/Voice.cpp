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
    float oscOutput = oscillator.oscillatorProcess();
    float filterOutput = LPF.filterProcess(oscOutput, 0);
    float ampOutput = filterOutput * ampEnvelope.ADSRProcess();
    return ampOutput;
}

void VoiceClass::newNote (int midiNote)
{
    oscillator.setFrequency(midiNoteToHz (midiNote));
    ampEnvelope.keyDown();
}

float VoiceClass::midiNoteToHz (int midiNote)
{
    return 400.0f * std::powf (2.0f, (midiNote - 69.0f) / 12.0f);
}

void VoiceClass::noteRelease()
{
    //oscillator.stop();
    ampEnvelope.keyUp();
}

bool VoiceClass::isPlaying()
{
    return ampEnvelope.isActive();
}

void VoiceClass::prepareToPlay()
{
    ampEnvelope.setAttack (2000);
    ampEnvelope.setRelease (2000);
    ampEnvelope.setDecay (2000);
    ampEnvelope.setSustain (0.5f);
    LPF.setLowPassCo (500.0f, 3.0f);
}

void VoiceClass::setSampleRate(float newValue) 
{ 
    sampleRate = newValue; 
    oscillator.setSampleRate (sampleRate); 
    ampEnvelope.setSampleRate (sampleRate); 
    LPF.setSampleRate (sampleRate);

}


