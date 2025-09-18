#pragma once

#include <JuceHeader.h>

// كلاس البلوجن الأساسي
class EltraV1AudioProcessor  : public juce::AudioProcessor
{
public:
    EltraV1AudioProcessor();
    ~EltraV1AudioProcessor() override = default;

    // إعدادات أساسية للبلوجن
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    // إعدادات للـ Editor
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    // إعدادات المشروع العامة
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    // إعدادات القنوات
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    // حفظ واسترجاع إعدادات البلوجن
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EltraV1AudioProcessor)
};
