#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EltraV1AudioProcessor::EltraV1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
#endif
{
}

EltraV1AudioProcessor::~EltraV1AudioProcessor() {}

//==============================================================================
const juce::String EltraV1AudioProcessor::getName() const { return JucePlugin_Name; }
bool EltraV1AudioProcessor::acceptsMidi() const { return false; }
bool EltraV1AudioProcessor::producesMidi() const { return false; }
bool EltraV1AudioProcessor::isMidiEffect() const { return false; }
double EltraV1AudioProcessor::getTailLengthSeconds() const { return 0.0; }

int EltraV1AudioProcessor::getNumPrograms() { return 1; }
int EltraV1AudioProcessor::getCurrentProgram() { return 0; }
void EltraV1AudioProcessor::setCurrentProgram (int) {}
const juce::String EltraV1AudioProcessor::getProgramName (int) { return {}; }
void EltraV1AudioProcessor::changeProgramName (int, const juce::String&) {}

//==============================================================================
void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    reverb.prepare(spec);
}

void EltraV1AudioProcessor::releaseResources() {}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    reverb.process(context);
}

//==============================================================================
bool EltraV1AudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor() { return new juce::GenericAudioProcessorEditor (*this); }

//==============================================================================
void EltraV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}
void EltraV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}
