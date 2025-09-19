#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
                                     .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    reverbParams.roomSize = 0.7f;
    reverbParams.damping = 0.5f;
    reverbParams.wetLevel = 0.6f;
    reverbParams.dryLevel = 0.5f;
    reverbParams.width = 1.0f;
    reverb.setParameters(reverbParams);
}

void EltraV1AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    reverb.prepare(spec);
}

void EltraV1AudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block(buffer);
    reverb.process(juce::dsp::ProcessContextReplacing<float>(block));
}

juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor()
{
    return new EltraV1AudioProcessorEditor(*this);
