#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
#endif
{
    addParameter(mixParam = new juce::AudioParameterFloat("mix", "Mix", 0.0f, 1.0f, 0.5f));
    addParameter(decayParam = new juce::AudioParameterFloat("decay", "Decay", 0.1f, 10.0f, 2.0f));
    addParameter(preDelayParam = new juce::AudioParameterFloat("predelay", "PreDelay", 0.0f, 500.0f, 50.0f));
    addParameter(toneParam = new juce::AudioParameterFloat("tone", "Tone", 100.0f, 10000.0f, 5000.0f));
    addParameter(softModeParam = new juce::AudioParameterBool("softmode", "Soft Mode", true));
}

EltraV1AudioProcessor::~EltraV1AudioProcessor() {}

const juce::String EltraV1AudioProcessor::getName() const { return "Eltra V1"; }

bool EltraV1AudioProcessor::acceptsMidi() const { return false; }
bool EltraV1AudioProcessor::producesMidi() const { return false; }
bool EltraV1AudioProcessor::isMidiEffect() const { return false; }
double EltraV1AudioProcessor::getTailLengthSeconds() const { return 5.0; }

int EltraV1AudioProcessor::getNumPrograms() { return 1; }
int EltraV1AudioProcessor::getCurrentProgram() { return 0; }
void EltraV1AudioProcessor::setCurrentProgram (int) {}
const juce::String EltraV1AudioProcessor::getProgramName (int) { return {}; }
void EltraV1AudioProcessor::changeProgramName (int, const juce::String&) {}

void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec { sampleRate, static_cast<juce::uint32> (samplesPerBlock), (juce::uint32) getTotalNumOutputChannels() };
    reverb.prepare(spec);
}

void EltraV1AudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EltraV1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}
#endif

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    // Update reverb parameters from GUI
    reverbParams.roomSize = (*decayParam) / 10.0f; 
    reverbParams.damping = 1.0f - ( (*toneParam) / 10000.0f );
    reverbParams.wetLevel = *mixParam;
    reverbParams.dryLevel = 1.0f - *mixParam;
    reverbParams.width = (*softModeParam) ? 1.0f : 0.5f;
    reverb.setParameters(reverbParams);

    juce::dsp::AudioBlock<float> block (buffer);
    reverb.process(juce::dsp::ProcessContextReplacing<float> (block));
}

void EltraV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData) 
{
    // Simple state saving (for presets)
    juce::MemoryOutputStream stream(destData, true);
    stream.writeFloat(*mixParam);
    stream.writeFloat(*decayParam);
    stream.writeFloat(*preDelayParam);
    stream.writeFloat(*toneParam);
    stream.writeBool(*softModeParam);
}

void EltraV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes) 
{
    juce::MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);
    mixParam->operator=(stream.readFloat());
    decayParam->operator=(stream.readFloat());
    preDelayParam->operator=(stream.readFloat());
    toneParam->operator=(stream.readFloat());
    softModeParam->operator=(stream.readBool());
}