/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
//==============================================================================
/**
*/
class PolySynthTemplateAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PolySynthTemplateAudioProcessorEditor (PolySynthTemplateAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~PolySynthTemplateAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolySynthTemplateAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& valueTreeState;
    
    juce::Slider waveSlider;
    juce::Slider fineSlider;
    juce::Slider coarseSlider;
    juce::Slider widthSlider;
    
    juce::Slider cutoffSlider;
    juce::Slider resonanceSlider;    
    
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    std::unique_ptr<SliderAttachment> waveAttachment;

    std::unique_ptr<SliderAttachment> cutoffAttachment;
    std::unique_ptr<SliderAttachment> resonanceAttachment;

    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    void setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolySynthTemplateAudioProcessorEditor)
};
