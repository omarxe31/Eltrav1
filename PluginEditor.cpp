#include "PluginEditor.h"

EltraV1AudioProcessorEditor::EltraV1AudioProcessorEditor (EltraV1AudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (500, 320);

    // Mix
    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    mixSlider.setRange(0.0, 1.0, 0.01);
    mixSlider.setValue(*processorRef.mixParam);
    mixSlider.addListener(this);
    addAndMakeVisible(&mixSlider);

    // Decay
    decaySlider.setSliderStyle(juce::Slider::Rotary);
    decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    decaySlider.setRange(0.1, 10.0, 0.1);
    decaySlider.setValue(*processorRef.decayParam);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);

    // PreDelay
    preDelaySlider.setSliderStyle(juce::Slider::Rotary);
    preDelaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    preDelaySlider.setRange(0.0, 500.0, 1.0);
    preDelaySlider.setValue(*processorRef.preDelayParam);
    preDelaySlider.addListener(this);
    addAndMakeVisible(&preDelaySlider);

    // Tone
    toneSlider.setSliderStyle(juce::Slider::Rotary);
    toneSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20);
    toneSlider.setRange(100.0, 10000.0, 10.0);
    toneSlider.setValue(*processorRef.toneParam);
    toneSlider.addListener(this);
    addAndMakeVisible(&toneSlider);

    // Soft/Hard toggle
    softHardButton.setButtonText("Soft");
    softHardButton.setToggleState(*processorRef.softModeParam, juce::dontSendNotification);
    softHardButton.addListener(this);
    addAndMakeVisible(&softHardButton);

    // Light/Dark toggle
    lightDarkButton.setButtonText("Light/Dark");
    lightDarkButton.setToggleState(true, juce::dontSendNotification);
    lightDarkButton.addListener(this);
    addAndMakeVisible(&lightDarkButton);
}

EltraV1AudioProcessorEditor::~EltraV1AudioProcessorEditor() {}

void EltraV1AudioProcessorEditor::paint (juce::Graphics& g)
{
    bool light = lightDarkButton.getToggleState();
    g.fillAll(light ? juce::Colour::fromFloatRGBA(0.97f,0.97f,0.98f,1.0f) : juce::Colours::black);

    g.setColour(light ? juce::Colours::black : juce::Colours::white);
    g.setFont(juce::Font(18.0f, juce::Font::bold));
    g.drawFittedText("Eltra V1", 12, 12, 200, 30, juce::Justification::left, 1);

    // Draw Al8iser logo/text bottom-left
    g.setFont(juce::Font(12.0f));
    g.drawFittedText("Al8iser", 12, getHeight() - 24, 120, 20, juce::Justification::left, 1);
}

void EltraV1AudioProcessorEditor::resized()
{
    int padding = 24;
    int sliderSize = 120;

    int x1 = padding;
    int x2 = padding + sliderSize + padding;
    int y1 = 60;

    mixSlider.setBounds(x1, y1, sliderSize, sliderSize);
    decaySlider.setBounds(x2, y1, sliderSize, sliderSize);
    preDelaySlider.setBounds(x1, y1 + sliderSize + padding, sliderSize, sliderSize);
    toneSlider.setBounds(x2, y1 + sliderSize + padding, sliderSize, sliderSize);

    softHardButton.setBounds(getWidth() - 120, 40, 100, 28);
    lightDarkButton.setBounds(getWidth() - 120, 80, 100, 28);
}

void EltraV1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if(slider == &mixSlider) processorRef.mixParam->setValueNotifyingHost((float)mixSlider.getValue());
    else if(slider == &decaySlider) processorRef.decayParam->setValueNotifyingHost((float)decaySlider.getValue());
    else if(slider == &preDelaySlider) processorRef.preDelayParam->setValueNotifyingHost((float)preDelaySlider.getValue());
    else if(slider == &toneSlider) processorRef.toneParam->setValueNotifyingHost((float)toneSlider.getValue());
}

void EltraV1AudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if(button == &softHardButton)
    {
        bool now = softHardButton.getToggleState();
        softHardButton.setButtonText(now ? "Soft" : "Hard");
        processorRef.softModeParam->setValueNotifyingHost(now);
    }
}