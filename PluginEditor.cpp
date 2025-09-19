#include "PluginEditor.h"

EltraV1AudioProcessorEditor::EltraV1AudioProcessorEditor (EltraV1AudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    setSize(400, 300);

    titleLabel.setText("Al8iser Reverb", juce::dontSendNotification);
    titleLabel.setJustificationType(juce::Justification::centred);
    titleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    addAndMakeVisible(titleLabel);

    auto setupSlider = [&](juce::Slider& slider, const juce::String& name)
    {
        slider.setSliderStyle(juce::Slider::Rotary);
        slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        slider.setName(name);
        addAndMakeVisible(slider);
    };

    setupSlider(roomSizeSlider, "Room Size");
    setupSlider(dampingSlider,  "Damping");
    setupSlider(widthSlider,    "Width");
    setupSlider(mixSlider,      "Mix");

    roomSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.parameters, "roomSize", roomSizeSlider);
    dampingAttachment  = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.parameters, "damping",  dampingSlider);
    widthAttachment    = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.parameters, "width",    widthSlider);
    mixAttachment      = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.parameters, "mix",      mixSlider);
}

void EltraV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkslategrey);
    g.setColour(juce::Colours::white);
    g.drawRect(getLocalBounds(), 1);
}

void EltraV1AudioProcessorEditor::resized()
{
    titleLabel.setBounds(0, 10, getWidth(), 30);
    
    auto area = getLocalBounds().reduced(40);
    auto sliderArea = area.removeFromBottom(area.getHeight() - 50);
    int sliderWidth = sliderArea.getWidth() / 4;

    roomSizeSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(10));
    dampingSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(10));
    widthSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(10));
    mixSlider.setBounds(sliderArea.removeFromLeft(sliderWidth).reduced(10));
}
