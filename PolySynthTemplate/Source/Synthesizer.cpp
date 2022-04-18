/*
  ==============================================================================

    Synthesizer.cpp
    Created: 12 Apr 2022 2:11:55pm
    Author:  Matthew Williams

  ==============================================================================
*/

#include "Synthesizer.h"

SynthesizerClass::SynthesizerClass(float samplerate) : sampleRate(samplerate)
{

}

void SynthesizerClass::prepareToPlay(double samplerate)
{
    for (VoiceClass voice : voices)
    {
        voice.setSampleRate(static_cast<float>(samplerate));
        voice.prepareToPlay();
    }
}


void SynthesizerClass::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
auto currentSample = 0;

for (const auto midiMessage : midiMessages)
{
    const auto midiEvent = midiMessage.getMessage();
    const auto midiEventSample = static_cast<int>(midiEvent.getTimeStamp());

    render(buffer, currentSample, midiEventSample);
    handleMidiEvent(midiEvent);

    currentSample = midiEventSample;
}
render(buffer, currentSample, buffer.getNumSamples());

}

void SynthesizerClass::handleMidiEvent(const juce::MidiMessage& midiEvent)
{
    if (midiEvent.isNoteOn())
    {
        //const auto oscillatorId = midiEvent.getNoteNumber();
        //const auto frequency = midiToHz(oscillatorId);
        for (int i = 0; i < NUM_VOICES; i++)
        {
            if (voices[i].isPlaying() == false)
            {
                voices[i].newNote(static_cast<int>(midiEvent.getNoteNumber()));
                activeNoteID[i] = static_cast<int>(midiEvent.getNoteNumber());
                break;
            }
        }
    }
    else if (midiEvent.isNoteOff())
    {
        //const auto oscillatorId = midiEvent.getNoteNumber();
        //oscillators[oscillatorId].stop();
        for (int i = 0; i < NUM_VOICES; i++)
        {
            if (activeNoteID[i] == static_cast<int>(midiEvent.getNoteNumber()))
            {
                voices[i].noteRelease();
                break;
            }
        }
    }
    /*else if (midiEvent.isAllNotesOff())
    {
        for (auto& oscillator : oscillators)
        {
            oscillator.stop();
        }

    }
    */
}

void SynthesizerClass::render(juce::AudioBuffer<float>& buffer, int startSample, int endSample)
{
    auto* firstChannel = buffer.getWritePointer(0);
    for (VoiceClass voice : voices)
    {
        if (voice.isPlaying())
        {
            for (auto sample = startSample; sample < endSample; ++sample)
            {
                firstChannel[sample] += voice.voiceProcess();
            }
        }
    }

    for (auto channel = 1; channel < buffer.getNumChannels(); channel++)
    {
        std::copy(firstChannel + startSample, firstChannel + endSample, buffer.getWritePointer(channel) + startSample);
    }
}
