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

    osc2FineSlider.setSkewFactorFromMidPoint(1);    
    setSlider(osc1ShapeSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc1FineSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);  
    setSlider(osc1CoarseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);    
    
    setSlider(osc2ShapeSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc2FineSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc2CoarseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(osc3ShapeSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc3FineSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(osc3CoarseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(widthSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(cutoffSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(resonanceSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);

    setSlider(attackSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(decaySlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(sustainSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    setSlider(releaseSlider, juce::Colours::red, juce::Slider::SliderStyle::LinearVertical);
    
    osc1ShapeAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SHAPE_1", osc1ShapeSlider);
    osc1FineAttachment = std::make_unique<SliderAttachment>(valueTreeState, "FINE_1", osc1FineSlider);
    osc1CoarseAttachment = std::make_unique<SliderAttachment>(valueTreeState, "COARSE_1", osc1CoarseSlider);

    osc2ShapeAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SHAPE_2", osc2ShapeSlider);
    osc2FineAttachment = std::make_unique<SliderAttachment>(valueTreeState, "FINE_2", osc2FineSlider);
    osc2CoarseAttachment = std::make_unique<SliderAttachment>(valueTreeState, "COARSE_2", osc2CoarseSlider);

    osc3ShapeAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SHAPE_3", osc3ShapeSlider);
    osc3FineAttachment = std::make_unique<SliderAttachment>(valueTreeState, "FINE_3", osc3FineSlider);
    osc3CoarseAttachment = std::make_unique<SliderAttachment>(valueTreeState, "COARSE_3", osc3CoarseSlider);

    cutoffAttachment = std::make_unique<SliderAttachment>(valueTreeState, "CUTOFF", cutoffSlider);
    resonanceAttachment = std::make_unique<SliderAttachment>(valueTreeState, "RESONANCE", resonanceSlider);

    attackAttachment = std::make_unique<SliderAttachment>(valueTreeState, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(valueTreeState, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(valueTreeState, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(valueTreeState, "RELEASE", releaseSlider);



    setSize (530, 300);
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
    osc1ShapeSlider.setBounds(20, 20, 30, 80);
    osc1FineSlider.setBounds(50, 20, 30, 80);
    osc1CoarseSlider.setBounds(80, 20, 30, 80);


    osc2ShapeSlider.setBounds(120, 20, 30, 80);
    osc2FineSlider.setBounds(150, 20, 30, 80);
    osc2CoarseSlider.setBounds(180, 20, 30, 80);

    osc3ShapeSlider.setBounds(220, 20, 30, 80);
    osc3FineSlider.setBounds(250, 20, 30, 80);
    osc3CoarseSlider.setBounds(280, 20, 30, 80);
    

    cutoffSlider.setBounds(320, 20, 30, 80);
    resonanceSlider.setBounds(350, 20, 30, 80);


    attackSlider.setBounds(390, 20, 30, 80);
    decaySlider.setBounds(420, 20, 30, 80);
    sustainSlider.setBounds(450, 20, 30, 80);
    releaseSlider.setBounds(480, 20, 30, 80);


}

void PolySynthTemplateAudioProcessorEditor::setSlider(juce::Slider& slider, juce::Colour colour, juce::Slider::SliderStyle style)
{
    addAndMakeVisible(slider);
    slider.setSliderStyle(style);
    //slider.setTextBoxStyle(juce::Slider::NoTextBox, false, 50, 10);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 10);

    slider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentWhite);
    slider.setColour(juce::Slider::thumbColourId, colour);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::black);
}
