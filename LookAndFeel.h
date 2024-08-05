/*
 ==============================================================================
    Copyright (c) 2024 MacielGUI
 ==============================================================================
 */

#pragma once

#include "juce_graphics/juce_graphics.h" // Inclui a biblioteca gráfica JUCE

namespace MacielGUI
{

// Classe LookAndFeel personalizada para o namespace MacielGUI
class LookAndFeel : public juce::LookAndFeel_V4
{
public:
    // Construtor da classe
    LookAndFeel();

    // Função que desenha o Slider rotativo personalizado
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    // Função que desenha a aparência personalizada de uma combo box
    void drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override;

    // Função que define a posição do texto dentro da combo box
    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override;

    // Função que desenha a aparência personalizada de um botão de aba
    void drawTabButton (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown) override;
};

} // namespace MacielGUI
