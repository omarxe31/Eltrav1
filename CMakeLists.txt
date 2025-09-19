cmake_minimum_required(VERSION 3.15)

project(EltraV1 VERSION 1.0.0)

# استخدم C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# لو JUCE مش موجودة، نزلها أوتوماتيكياً
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/JUCE")
    message(STATUS "Downloading JUCE...")
    execute_process(
        COMMAND git clone --branch 7.0.12 https://github.com/juce-framework/JUCE.git
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

# أضف JUCE للمشروع
add_subdirectory(JUCE)

# أضف البلوجن
juce_add_plugin(EltraV1
    COMPANY_NAME "Al8iser"
    PLUGIN_MANUFACTURER_CODE Al8s
    PLUGIN_CODE Etr1
    FORMATS VST3
    PRODUCT_NAME "EltraV1"
)

# أضف ملفات الكود
target_sources(EltraV1 PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
)

# إعدادات JUCE لتعطيل الموديلات اللي مش هنستخدمها
target_compile_definitions(EltraV1 PRIVATE
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
)

# اربط مع JUCE Audio Utils
target_link_libraries(EltraV1 PRIVATE
    juce::juce_audio_utils
    juce::juce_gui_extra
    juce::juce_dsp
)
