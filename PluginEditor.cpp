#include "PluginEditor.h"

EltraV1AudioProcessorEditor::EltraV1AudioProcessorEditor (EltraV1AudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    setSize(400, 300);

    gainSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(gainSlider);

    gainLabel.setText("Gain", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);

    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        processor.parameters, "gain", gainSlider);
}

EltraV1AudioProcessorEditor::~EltraV1AudioProcessorEditor() {}

void EltraV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawFittedText("EltraV1 - Gain Control", getLocalBounds(), juce::Justification::centredTop, 1);
}

void EltraV1AudioProcessorEditor::resized()
{
    gainSlider.setBounds(getWidth()/2 - 50, getHeight()/2 - 50, 100, 100);
}
