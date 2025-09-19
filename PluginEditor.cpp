#include "PluginEditor.h"

EltraV1AudioProcessorEditor::EltraV1AudioProcessorEditor(EltraV1AudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(400, 300);
}

void EltraV1AudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::aqua);
    g.setFont(24.0f);
    g.drawFittedText("Al8iser Reverb", getLocalBounds(), juce::Justification::centred, 1);
}

void EltraV1AudioProcessorEditor::resized()
{
}
