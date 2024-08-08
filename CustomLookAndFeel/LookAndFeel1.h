/*
 ==============================================================================
    Copyright (c) 2024 MacielGUI
 ==============================================================================
 */

#pragma once

#include "juce_graphics/juce_graphics.h" 

namespace MacielGUI
{

class LookAndFeel : public juce::LookAndFeel_V4
{
public:

    LookAndFeel();

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    void drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override;

    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override;

    void drawTabButton (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown) override;
};

} 
