#include "PluginEditor.h"

EltraV1AudioProcessorEditor::EltraV1AudioProcessorEditor (EltraV1AudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (520, 320);

    // Mix
    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(mixSlider);
    mixAttachment.reset(new SliderAttachment(processorRef.apvts, "mix", mixSlider));

    // Decay
    decaySlider.setSliderStyle(juce::Slider::Rotary);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(decaySlider);
    decayAttachment.reset(new SliderAttachment(processorRef.apvts, "decay", decaySlider));

    // PreDelay (not applied yet, placeholder)
    preDelaySlider.setSliderStyle(juce::Slider::Rotary);
    preDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(preDelaySlider);
    preDelayAttachment.reset(new SliderAttachment(processorRef.apvts, "predelay", preDelaySlider));

    // Tone/Damping
    toneSlider.setSliderStyle(juce::Slider::Rotary);
    toneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    addAndMakeVisible(toneSlider);
    toneAttachment.reset(new SliderAttachment(processorRef.apvts, "tone", toneSlider));

    // Soft/Hard
    softHardButton.setButtonText("Soft");
    addAndMakeVisible(softHardButton);
    softAttachment.reset(new ButtonAttachment(processorRef.apvts, "softmode", softHardButton));

    // Light/Dark toggle
    lightDarkButton.setButtonText("Light/Dark");
    lightDarkButton.setToggleState(true, juce::dontSendNotification);
    addAndMakeVisible(lightDarkButton);
}

EltraV1AudioProcessorEditor::~EltraV1AudioProcessorEditor() {}

void EltraV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    bool light = lightDarkButton.getToggleState();
    g.fillAll(light ? juce::Colours::white : juce::Colours::darkgrey);

    g.setColour(light ? juce::Colours::black : juce::Colours::white);
    g.setFont(juce::Font(18.0f, juce::Font::bold));
    g.drawFittedText("Eltra V1 - Al8iser", 16, 10, 300, 30, juce::Justification::left, 1);

    g.setFont(juce::Font(12.0f));
    g.drawFittedText("Mix", 40, 120, 100, 20, juce::Justification::centred, 1);
    g.drawFittedText("Decay", 190, 120, 100, 20, juce::Justification::centred, 1);
    g.drawFittedText("PreDelay", 340, 120, 100, 20, juce::Justification::centred, 1);
    g.drawFittedText("Tone", 40, 260, 100, 20, juce::Justification::centred, 1);
}

void EltraV1AudioProcessorEditor::resized()
{
    int w = getWidth();
    int h = getHeight();

    int sliderSize = 120;
    mixSlider.setBounds(20, 40, sliderSize, sliderSize);
    decaySlider.setBounds(170, 40, sliderSize, sliderSize);
    preDelaySlider.setBounds(320, 40, sliderSize, sliderSize);
    toneSlider.setBounds(20, 180, sliderSize, sliderSize);

    softHardButton.setBounds(w - 140, 40, 100, 28);
    lightDarkButton.setBounds(w - 140, 80, 100, 28);
}
