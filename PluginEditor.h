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
    EltraV1AudioProcessor& processorRef;

    juce::Slider mixSlider;
    juce::Slider decaySlider;
    juce::Slider preDelaySlider;
    juce::Slider toneSlider;

    juce::ToggleButton softHardButton;
    juce::ToggleButton lightDarkButton;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    std::unique_ptr<SliderAttachment> mixAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> preDelayAttachment;
    std::unique_ptr<SliderAttachment> toneAttachment;
    std::unique_ptr<ButtonAttachment> softAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EltraV1AudioProcessorEditor)
};
