#pragma once

#include <JuceHeader.h>

namespace Colors
{
    const juce::Colour background { juce::Colour(1, 1, 1) }; 
    const juce::Colour header { juce::Colour(50, 50, 50) }; 
    
    namespace Knob
    {
        const juce::Colour trackBackground { juce::Colour(220, 220, 220) }; 
        const juce::Colour trackActive { juce::Colour(150, 150, 150) }; 
        const juce::Colour outline { juce::Colour(240, 240, 240) }; 
        const juce::Colour gradientTop { juce::Colour(180, 180, 180) }; 
        const juce::Colour gradientBottom { juce::Colour(1, 1, 1) }; 
        const juce::Colour dial { juce::Colour(10, 10, 10) }; 
        const juce::Colour dropShadow { juce::Colour(150, 150, 150) }; 
        const juce::Colour label { juce::Colour(60, 60, 60) }; 
        const juce::Colour textBoxBackground { juce::Colour(23, 23, 23) }; 
        const juce::Colour value { juce::Colour(240, 240, 240) }; 
        const juce::Colour caret { juce::Colour(60, 60, 60) }; 
    }
    
    namespace Button
    {
        const juce::Colour text { juce::Colour(60, 60, 60) }; 
        const juce::Colour background { juce::Colour(21, 21, 21) }; 
        const juce::Colour border { juce::Colour(180, 180, 180) }; 
    }
}

class KnobLookAndFeel : public juce::LookAndFeel_V4
{
public:
    KnobLookAndFeel();
    ~KnobLookAndFeel() override;
    
    static KnobLookAndFeel* get()
    {
        static KnobLookAndFeel instance;
        return  &instance;
    }
    
    void drawRotarySlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour, bool isMouseOverButton, bool isButtonDown) override;
    juce::Font getTextButtonFont (juce::TextButton&, int buttonHeight) override;
    
private:
    juce::DropShadow dropShadow { Colors::Knob::dropShadow, 6, { 0, 3 } };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(KnobLookAndFeel)
};
