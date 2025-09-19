cmake_minimum_required(VERSION 3.15)

project(EltraV1 VERSION 0.0.1)

# إضافة JUCE كمكتبة
add_subdirectory(JUCE)

# إعداد البلوجن
juce_add_plugin(EltraV1
    COMPANY_NAME "Al8iser"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Al8i
    PLUGIN_CODE Eltr
    FORMATS VST3
    PRODUCT_NAME "EltraV1"
)

# ملفات البلوجن
target_sources(EltraV1
    PRIVATE
        PluginProcessor.cpp
        PluginProcessor.h
        PluginEditor.cpp
        PluginEditor.h
)

# ربط JUCE بالمشروع
target_link_libraries(EltraV1 PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_basics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_dsp
)
