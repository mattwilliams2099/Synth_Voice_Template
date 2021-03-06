/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolySynthTemplateAudioProcessor::PolySynthTemplateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, juce::Identifier("delayValueTree"),
                           {
                                std::make_unique<juce::AudioParameterInt>   ("SHAPE_1",     "Osc 1 Shape",  0,      3,          0),
                                std::make_unique<juce::AudioParameterFloat> ("FINE_1",      "Osc 1 Fine",   0.5f,   2.0f,       1.0f),
                                std::make_unique<juce::AudioParameterFloat> ("COARSE_1",    "Osc 1 Coarse", 0.125f, 8.0f,       1.0f),

                                std::make_unique<juce::AudioParameterInt>   ("SHAPE_2",     "Osc 2 Shape",  0,      3,          0),
                                std::make_unique<juce::AudioParameterFloat> ("FINE_2",      "Osc 2 Fine",   0.5f,   2.0f,       1.0f),
                                std::make_unique<juce::AudioParameterFloat> ("COARSE_2",    "Osc 2 Coarse", 0.125f, 8.0f,       1.0f),

                                std::make_unique<juce::AudioParameterInt>   ("SHAPE_3",     "Osc 3 Shape",  0,      3,          0),
                                std::make_unique<juce::AudioParameterFloat> ("FINE_3",      "Osc 3 Fine",   0.5f,   2.0f,       1.0f),
                                std::make_unique<juce::AudioParameterFloat> ("COARSE_3",    "Osc 3 Coarse", 0.125f, 8.0f,       1.0f),

                                std::make_unique<juce::AudioParameterFloat> ("CUTOFF",      "Cutoff",       10.0f,  20000.0f,   20000.0f),
                                std::make_unique<juce::AudioParameterFloat> ("RESONANCE",   "Resonance",    0.1f,   8.0f,       1.0f),

                                std::make_unique<juce::AudioParameterInt>   ("ATTACK",      "Attack",       1,      1000,       500),
                                std::make_unique<juce::AudioParameterInt>   ("DECAY",       "Decay",        1,      1000,       500),
                                std::make_unique<juce::AudioParameterFloat> ("SUSTAIN",     "Sustain",      0.0f,   1.0f,       0.5f),
                                std::make_unique<juce::AudioParameterInt>   ("RELEASE",     "Release",      1,      1000,       500)
                           })
#endif
{
    shape1Parameter = parameters.getRawParameterValue("SHAPE_1");
    osc1FineParameter = parameters.getRawParameterValue("FINE_1");
    osc1CoarseParameter = parameters.getRawParameterValue("COARSE_1");

    shape2Parameter = parameters.getRawParameterValue("SHAPE_2");
    osc2FineParameter = parameters.getRawParameterValue("FINE_2");
    osc2CoarseParameter = parameters.getRawParameterValue("COARSE_2");

    shape3Parameter = parameters.getRawParameterValue("SHAPE_3");
    osc3FineParameter = parameters.getRawParameterValue("FINE_3");
    osc3CoarseParameter = parameters.getRawParameterValue("COARSE_3");

    cutoffParameter = parameters.getRawParameterValue("CUTOFF");
    resonanceParameter = parameters.getRawParameterValue("RESONANCE");
    attackParameter = parameters.getRawParameterValue("ATTACK");
    decayParameter = parameters.getRawParameterValue("DECAY");
    sustainParameter = parameters.getRawParameterValue("SUSTAIN");
    releaseParameter = parameters.getRawParameterValue("RELEASE");

}

PolySynthTemplateAudioProcessor::~PolySynthTemplateAudioProcessor()
{
}

//==============================================================================
const juce::String PolySynthTemplateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PolySynthTemplateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PolySynthTemplateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PolySynthTemplateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PolySynthTemplateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PolySynthTemplateAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PolySynthTemplateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PolySynthTemplateAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PolySynthTemplateAudioProcessor::getProgramName (int index)
{
    return {};
}

void PolySynthTemplateAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PolySynthTemplateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synthesizer.prepareToPlay(sampleRate);
}

void PolySynthTemplateAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PolySynthTemplateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PolySynthTemplateAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();

    synthesizer.setOscShape(*shape1Parameter, 0);
    synthesizer.setOscFineFreq(*osc1FineParameter, 0);
    synthesizer.setOscCoarseFreq(*osc1CoarseParameter, 0);

    synthesizer.setOscShape(*shape2Parameter, 1);
    synthesizer.setOscFineFreq(*osc2FineParameter, 1);
    synthesizer.setOscCoarseFreq(*osc2CoarseParameter, 1);

    synthesizer.setOscShape(*shape3Parameter, 2);
    synthesizer.setOscFineFreq(*osc3FineParameter, 2);
    synthesizer.setOscCoarseFreq(*osc3CoarseParameter, 2);

    synthesizer.setFilter(*cutoffParameter, *resonanceParameter);

    synthesizer.setAmpAttack(*attackParameter);
    synthesizer.setAmpDecay(*decayParameter);
    synthesizer.setAmpSustain(*sustainParameter);
    synthesizer.setAmpRelease(*releaseParameter);

    synthesizer.processBlock(buffer, midiMessages);
}

//==============================================================================
bool PolySynthTemplateAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PolySynthTemplateAudioProcessor::createEditor()
{
    return new PolySynthTemplateAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void PolySynthTemplateAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PolySynthTemplateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolySynthTemplateAudioProcessor();
}
