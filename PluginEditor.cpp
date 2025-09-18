#include "PluginEditor.h"

EltraV1AudioProcessorEditor::EltraV1AudioProcessorEditor (EltraV1AudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (400, 300);
}

EltraV1AudioProcessorEditor::~EltraV1AudioProcessorEditor() {}

void EltraV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("EltraV1 Plugin by Al8iser", getLocalBounds(), juce::Justification::centred, 1);
}

void EltraV1AudioProcessorEditor::resized() {}
