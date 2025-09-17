#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class EltraV1AudioProcessorEditor  : public juce::AudioProcessorEditor,
                                     public juce::Slider::Listener,
                                     public juce::Button::Listener
{
public:
    EltraV1AudioProcessorEditor (EltraV1AudioProcessor&);
    ~EltraV1AudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    EltraV1AudioProcessor& processorRef;

    juce::Slider mixSlider;
    juce::Slider decaySlider;
    juce::Slider preDelaySlider;
    juce::Slider toneSlider;

    juce::ToggleButton softHardButton; // Soft/Hard mode toggle
    juce::ToggleButton lightDarkButton; // Light/Dark mode

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EltraV1AudioProcessorEditor)
};