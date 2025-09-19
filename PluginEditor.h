#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class EltraV1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    EltraV1AudioProcessorEditor (EltraV1AudioProcessor&);
    ~EltraV1AudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    EltraV1AudioProcessor& processorRef;

    juce::Slider roomSizeSlider, dampingSlider, widthSlider, mixSlider;
    juce::Label titleLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment, dampingAttachment, widthAttachment, mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EltraV1AudioProcessorEditor)
};
