#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
    : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true))
{
}

void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {}
void EltraV1AudioProcessor::releaseResources() {}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    // هنا ممكن تضيف تأثيرك الصوتي، دلوقتي هيسيب الصوت زي ما هو
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        juce::ignoreUnused(channelData); // عشان ميبقاش في تحذير
    }
}

// إعدادات للـ Editor
juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor() { return new EltraV1AudioProcessorEditor (*this); }
bool EltraV1AudioProcessor::hasEditor() const { return true; }

const juce::String EltraV1AudioProcessor::getName() const { return "EltraV1"; }
bool EltraV1AudioProcessor::acceptsMidi() const { return false; }
bool EltraV1AudioProcessor::producesMidi() const { return false; }
double EltraV1AudioProcessor::getTailLengthSeconds() const { return 0.0; }

int EltraV1AudioProcessor::getNumPrograms() { return 1; }
int EltraV1AudioProcessor::getCurrentProgram() { return 0; }
void EltraV1AudioProcessor::setCurrentProgram (int index) { juce::ignoreUnused(index); }
const juce::String EltraV1AudioProcessor::getProgramName (int index) { juce::ignoreUnused(index); return {}; }
void EltraV1AudioProcessor::changeProgramName (int index, const juce::String& newName) { juce::ignoreUnused(index, newName); }

void EltraV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}
void EltraV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes) { juce::ignoreUnused(data, sizeInBytes); }

// الدالة المطلوبة عشان JUCE يعرف يبني البلوجن
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EltraV1AudioProcessor();
}
