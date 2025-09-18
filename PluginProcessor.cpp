#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor() {}
EltraV1AudioProcessor::~EltraV1AudioProcessor() {}

void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    reverb.setSampleRate(sampleRate);
    reverb.setParameters({ 0.5f, 0.5f, 0.5f, 0.5f, 0.5f }); // إعدادات افتراضية
}

void EltraV1AudioProcessor::releaseResources() {}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    reverb.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
}

juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor() { return new juce::GenericAudioProcessorEditor (*this); }
bool EltraV1AudioProcessor::hasEditor() const { return true; }

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

void EltraV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}
void EltraV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}
