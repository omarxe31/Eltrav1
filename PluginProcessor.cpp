#include "PluginProcessor.h"
#include "PluginEditor.h"

EltraV1AudioProcessor::EltraV1AudioProcessor()
 : AudioProcessor (BusesProperties()
        .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
   apvts(*this, nullptr, "PARAMS", createParameterLayout())
{
}

EltraV1AudioProcessor::~EltraV1AudioProcessor() = default;

juce::AudioProcessorValueTreeState::ParameterLayout EltraV1AudioProcessor::createParameterLayout()
{
    using Param = juce::AudioParameterFloat;
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<Param>("mix",   "Mix",   juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f));
    params.push_back(std::make_unique<Param>("decay", "Decay", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f)); // 0..1 mapped to roomSize
    params.push_back(std::make_unique<Param>("predelay", "PreDelay", juce::NormalisableRange<float>(0.0f, 500.0f), 50.0f)); // ms (for future)
    params.push_back(std::make_unique<Param>("tone",  "Tone",  juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f)); // mapped to damping
    params.push_back(std::make_unique<juce::AudioParameterBool>("softmode", "Soft Mode", true));

    return { params.begin(), params.end() };
}

void EltraV1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = static_cast<juce::uint32> (samplesPerBlock);
    spec.numChannels = static_cast<juce::uint32> (getTotalNumOutputChannels());

    reverb.reset();
    reverb.prepare(spec);

    wetBuffer.setSize(getTotalNumOutputChannels(), samplesPerBlock);
}

void EltraV1AudioProcessor::releaseResources() {}

void EltraV1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const int numChannels = buffer.getNumChannels();
    const int numSamples  = buffer.getNumSamples();

    // read params
    float mixVal   = *apvts.getRawParameterValue("mix");
    float decayVal = *apvts.getRawParameterValue("decay"); // 0..1
    float toneVal  = *apvts.getRawParameterValue("tone");  // 0..1
    float softVal  = *apvts.getRawParameterValue("softmode");

    bool softMode = (softVal > 0.5f);

    // prepare wetBuffer copy of input
    wetBuffer.makeCopyOf(buffer);

    // configure reverb (we process wet-only then mix manually)
    reverbParams.roomSize = decayVal;              // 0..1
    reverbParams.damping  = 1.0f - toneVal;        // invert tone -> damping
    reverbParams.wetLevel = 1.0f;                  // we want wet-only from reverb
    reverbParams.dryLevel = 0.0f;
    reverbParams.width    = softMode ? 1.0f : 0.5f;
    reverb.setParameters(reverbParams);

    // process wetBuffer through reverb
    juce::dsp::AudioBlock<float> wetBlock (wetBuffer);
    juce::dsp::ProcessContextReplacing<float> context (wetBlock);
    reverb.process(context);

    // mix: out = dry*(1-mix) + wet*mix
    for (int ch = 0; ch < numChannels; ++ch)
    {
        float* out = buffer.getWritePointer(ch);
        const float* wet = wetBuffer.getReadPointer(ch);

        for (int i = 0; i < numSamples; ++i)
        {
            out[i] = out[i] * (1.0f - mixVal) + wet[i] * mixVal;
        }
    }
}

juce::AudioProcessorEditor* EltraV1AudioProcessor::createEditor() { return new EltraV1AudioProcessorEditor (*this); }
bool EltraV1AudioProcessor::hasEditor() const { return true; }

const juce::String EltraV1AudioProcessor::getName() const { return "EltraV1"; }
bool EltraV1AudioProcessor::acceptsMidi() const { return false; }
bool EltraV1AudioProcessor::producesMidi() const { return false; }
double EltraV1AudioProcessor::getTailLengthSeconds() const { return 5.0; }

int EltraV1AudioProcessor::getNumPrograms() { return 1; }
int EltraV1AudioProcessor::getCurrentProgram() { return 0; }
void EltraV1AudioProcessor::setCurrentProgram (int) {}
const juce::String EltraV1AudioProcessor::getProgramName (int) { return {}; }
void EltraV1AudioProcessor::changeProgramName (int, const juce::String&) {}

void EltraV1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    if (auto xml = apvts.copyState().createXml())
        copyXmlToBinary (*xml, destData);
}

void EltraV1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (auto xml = getXmlFromBinary (data, sizeInBytes))
        apvts.replaceState (juce::ValueTree::fromXml (*xml));
}

// required factory function for old VST hosts / JUCE VST wrapper
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EltraV1AudioProcessor();
}
