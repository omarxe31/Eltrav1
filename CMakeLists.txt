cmake_minimum_required(VERSION 3.15)

project(EltraV1 VERSION 0.0.1)

# JUCE
add_subdirectory(JUCE)

juce_add_plugin(EltraV1
    COMPANY_NAME "Al8iser"
    BUNDLE_ID com.Al8iser.EltraV1
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    VST3_CATEGORY "Fx"
    FORMATS VST3
    PRODUCT_NAME "Al8iser"
)

target_sources(EltraV1
    PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
)

target_compile_features(EltraV1 PRIVATE cxx_std_17)

target_link_libraries(EltraV1 PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_core
)
