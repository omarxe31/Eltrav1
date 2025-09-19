#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
    : parameters(*this, nullptr, "PARAMETERS",
        { std::make_unique<juce::AudioParameterFloat>("roomSize", "Room Size", 0.0f, 1.0f, 0.5f),
          std::make_unique<juce::AudioParameterFloat>("damping", "Damping", 0.0f, 1.0f, 0.5f),
          std::make_unique<juce::AudioParameterFloat>("width", "Width", 0.0f, 1.0f, 1.0f),
          std::make_unique<juce::AudioParameterFloat>("mix", "Mix", 0.0f, 1.0f, 0.5f) })
{
}

void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    reverb.setSampleRate(sampleRate);
}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    buffer.clear();

    reverbParams.roomSize   = *parameters.getRawParameterValue("roomSize");
    reverbParams.damping    = *parameters.getRawParameterValue("damping");
    reverbParams.width      = *parameters.getRawParameterValue("width");
    reverbParams.wetLevel   = *parameters.getRawParameterValue("mix");
    reverbParams.dryLevel   = 1.0f - reverbParams.wetLevel;
    reverbParams.freezeMode = 0.0f;

    reverb.setParameters(reverbParams);
    reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor() { return new juce::GenericAudioProcessorEditor (*this); }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() { return new EltraV1AudioProcessor(); }
