#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

class EltraV1AudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    EltraV1AudioProcessorEditor(EltraV1AudioProcessor&);
    ~EltraV1AudioProcessorEditor() override = default;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    EltraV1AudioProcessor& processor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EltraV1AudioProcessorEditor)
};
