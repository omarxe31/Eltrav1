#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class EltraV1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EltraV1AudioProcessorEditor (EltraV1AudioProcessor&);
    ~EltraV1AudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    EltraV1AudioProcessor& processor;
    juce::Slider gainSlider;
    juce::Label gainLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EltraV1AudioProcessorEditor)
};
