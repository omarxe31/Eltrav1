#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
    : parameters(*this, nullptr, "PARAMETERS",
                 { std::make_unique<juce::AudioParameterFloat>("gain", "Gain", 0.0f, 1.0f, 0.5f) })
{
}

EltraV1AudioProcessor::~EltraV1AudioProcessor() {}

const juce::String EltraV1AudioProcessor::getName() const { return "EltraV1"; }

bool EltraV1AudioProcessor::acceptsMidi() const { return false; }
bool EltraV1AudioProcessor::producesMidi() const { return false; }
bool EltraV1AudioProcessor::isMidiEffect() const { return false; }
double EltraV1AudioProcessor::getTailLengthSeconds() const { return 0.0; }

int EltraV1AudioProcessor::getNumPrograms() { return 1; }
int EltraV1AudioProcessor::getCurrentProgram() { return 0; }
void EltraV1AudioProcessor::setCurrentProgram (int) {}
const juce::String EltraV1AudioProcessor::getProgramName (int) { return {}; }
void EltraV1AudioProcessor::changeProgramName (int, const juce::String&) {}

void EltraV1AudioProcessor::prepareToPlay (double, int) {}
void EltraV1AudioProcessor::releaseResources() {}

bool EltraV1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    auto gain = *parameters.getRawParameterValue("gain");
    buffer.applyGain(gain);
}

bool EltraV1AudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor() { return new EltraV1AudioProcessorEditor(*this); }

void EltraV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream stream(destData, true);
    parameters.state.writeToStream(stream);
}

void EltraV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) parameters.state = tree;
}
