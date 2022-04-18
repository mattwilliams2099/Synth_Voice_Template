/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolySynthTemplateAudioProcessorEditor::PolySynthTemplateAudioProcessorEditor (PolySynthTemplateAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSlider(waveSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(fineSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(coarseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(widthSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(cutoffSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(resonanceSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(attackSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(decaySlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(sustainSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(releaseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    
    waveAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SHAPE", waveSlider);
    
    cutoffAttachment = std::make_unique<SliderAttachment>(valueTreeState, "CUTOFF", cutoffSlider);
    resonanceAttachment = std::make_unique<SliderAttachment>(valueTreeState, "RESONANCE", resonanceSlider);

    attackAttachment = std::make_unique<SliderAttachment>(valueTreeState, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(valueTreeState, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(valueTreeState, "RELEASE", releaseSlider);




    setSize (400, 300);
}

PolySynthTemplateAudioProcessorEditor::~PolySynthTemplateAudioProcessorEditor()
{
}

//==============================================================================
void PolySynthTemplateAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::dimgrey);

    g.setColour (juce::Colours::white);
//g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PolySynthTemplateAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    waveSlider.setBounds(20, 20, 30, 80);
    fineSlider.setBounds(50, 20, 30, 80);
    coarseSlider.setBounds(80, 20, 30, 80);
    widthSlider.setBounds(110, 20, 30, 80);
    

    cutoffSlider.setBounds(160, 20, 30, 80);
    resonanceSlider.setBounds(190, 20, 30, 80);


    attackSlider.setBounds(230, 20, 30, 80);
    decaySlider.setBounds(260, 20, 30, 80);
    sustainSlider.setBounds(290, 20, 30, 80);
    releaseSlider.setBounds(320, 20, 30, 80);


}

void PolySynthTemplateAudioProcessorEditor::setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 10);
    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    slider.setColour(juce::Slider::thumbColourId, colour);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::black);
}
