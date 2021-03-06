/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synthesizer.h"
//==============================================================================
/**
*/
class PolySynthTemplateAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    PolySynthTemplateAudioProcessor();
    ~PolySynthTemplateAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    SynthesizerClass synthesizer{ static_cast<float>(this->getSampleRate()) };
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* shape1Parameter = nullptr;
    std::atomic<float>* osc1FineParameter = nullptr;
    std::atomic<float>* osc1CoarseParameter = nullptr;

    std::atomic<float>* shape2Parameter = nullptr;
    std::atomic<float>* osc2FineParameter = nullptr;    
    std::atomic<float>* osc2CoarseParameter = nullptr;    
    
    std::atomic<float>* shape3Parameter = nullptr;
    std::atomic<float>* osc3FineParameter = nullptr;
    std::atomic<float>* osc3CoarseParameter = nullptr;

    std::atomic<float>* cutoffParameter = nullptr;
    std::atomic<float>* resonanceParameter = nullptr;

    std::atomic<float>* attackParameter = nullptr;
    std::atomic<float>* decayParameter = nullptr;
    std::atomic<float>* sustainParameter = nullptr;
    std::atomic<float>* releaseParameter = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolySynthTemplateAudioProcessor)
};
