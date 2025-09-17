cmake_minimum_required(VERSION 3.15)

project(EltraV1 VERSION 1.0 LANGUAGES CXX)

# JUCE will be downloaded by the workflow; expect it to be at ${CMAKE_SOURCE_DIR}/JUCE
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/JUCE")

if(NOT EXISTS "${JUCE_DIR}/CMakeLists.txt")
  message(STATUS "JUCE not found in source; the CI workflow will clone JUCE automatically.")
endif()

add_subdirectory(${JUCE_DIR} EXCLUDE_FROM_ALL)

juce_add_plugin(EltraV1
    PLUGIN_MANUFACTURER_CODE Al8i
    PLUGIN_CODE ElV1
    FORMATS VST3
    PRODUCT_NAME "Eltra V1"
)

target_sources(EltraV1 PRIVATE
    PluginProcessor.cpp
    PluginProcessor.h
    PluginEditor.cpp
    PluginEditor.h
)

target_link_libraries(EltraV1 PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_gui_extra
    juce::juce_gui_basics
)

set_target_properties(EltraV1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/VST3"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/VST3"
)