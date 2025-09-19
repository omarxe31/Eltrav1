#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
    : parameters(*this, nullptr, "PARAMS", {
        std::make_unique<juce::AudioParameterFloat>("roomSize", "Room Size", 0.0f, 1.0f, 0.5f),
        std::make_unique<juce::AudioParameterFloat>("damping",  "Damping",   0.0f, 1.0f, 0.5f),
        std::make_unique<juce::AudioParameterFloat>("width",    "Width",     0.0f, 1.0f, 1.0f),
        std::make_unique<juce::AudioParameterFloat>("mix",      "Mix",       0.0f, 1.0f, 0.5f)
    })
{}

void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    reverb.setSampleRate(sampleRate);
}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    reverbParams.roomSize = *parameters.getRawParameterValue("roomSize");
    reverbParams.damping  = *parameters.getRawParameterValue("damping");
    reverbParams.width    = *parameters.getRawParameterValue("width");
    reverbParams.wetLevel = *parameters.getRawParameterValue("mix");
    reverbParams.dryLevel = 1.0f - reverbParams.wetLevel;
    
    reverb.setParameters(reverbParams);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        reverb.processMono(buffer.getWritePointer(channel), buffer.getNumSamples());
}

juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor()
{
    return new EltraV1AudioProcessorEditor (*this);
}
