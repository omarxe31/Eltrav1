cmake_minimum_required(VERSION 3.15)

project(EltraV1 VERSION 1.0.0)

# إعدادات أساسية
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# تنزيل JUCE لو مش موجود
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/JUCE")
    message(STATUS "Downloading JUCE...")
    execute_process(COMMAND git clone --branch 7.0.12 https://github.com/juce-framework/JUCE.git
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

# إضافة JUCE
add_subdirectory(JUCE)

# تعريف البلوجن
juce_add_plugin(EltraV1
    COMPANY_NAME "Al8iser"
    PLUGIN_MANUFACTURER_CODE Al8s
    PLUGIN_CODE Etr1
    FORMATS VST3
    PRODUCT_NAME "EltraV1"
)

# ملفات الكود
target_sources(EltraV1 PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
)

# توليد JuceHeader.h تلقائي
juce_generate_juce_header(EltraV1)

# إعدادات JUCE
target_compile_definitions(EltraV1 PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# اللينك مع JUCE
target_link_libraries(EltraV1 PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_audio_basics
    juce::juce_core
)
