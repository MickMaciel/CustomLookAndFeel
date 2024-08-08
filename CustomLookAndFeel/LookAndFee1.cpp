/*
 ==============================================================================
    Copyright (c) 2024 MacielGUI
 ==============================================================================
 */

#include "juce_graphics/juce_graphics.h" 

namespace MacielGUI
{

class LookAndFeel : public juce::LookAndFeel_V4
{
public:
    LookAndFeel()
    {
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        const auto outline = juce::Colour (0xff2b2b2b); 
        const auto fill    = juce::Colour (0xff4caf50);  
        const auto shadow  = juce::Colour (0x80000000);  
        const auto text    = juce::Colour (0xffffffff);  

        auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);
        auto centre = bounds.getCentre();

        const auto tickHeight = 6;
        const auto tickWidth  = 40;

        auto radius = juce::jmin (bounds.getWidth() / 2.0f, bounds.getHeight() / 2.0f);

        g.setColour (shadow);
        g.fillEllipse (centre.getX() - radius - 5, centre.getY() - radius - 5, radius * 2 + 10, radius * 2 + 10);

        g.setColour (text);
        if (radius > tickWidth * 2.0f + 10.0f)
        {
            const auto xLeft  = int (bounds.getX());
            const auto xRight = int (bounds.getRight() - tickWidth);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.5f)),   int (centre.getX() - tickWidth / 2), int (bounds.getY()), tickWidth, tickHeight, juce::Justification::centred, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.375f)), xLeft,  int (bounds.getY()), tickWidth, tickHeight, juce::Justification::left, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.25f)),  xLeft,  int (juce::jmap (0.33f,  float (bounds.getY()), bounds.getBottom() - tickHeight)), tickWidth, tickHeight, juce::Justification::left, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.125f)), xLeft,  int (juce::jmap (0.66f,  float (bounds.getY()), bounds.getBottom() - tickHeight)), tickWidth, tickHeight, juce::Justification::left, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.0f)),   xLeft,  int (bounds.getBottom() - tickHeight), tickWidth, tickHeight, juce::Justification::left, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.625f)), xRight, int (bounds.getY()), tickWidth, tickHeight, juce::Justification::right, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.75f)),  xRight, int (juce::jmap (0.33f,  float (bounds.getY()), bounds.getBottom() - tickHeight)), tickWidth, tickHeight, juce::Justification::right, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (0.875f)), xRight, int (juce::jmap (0.66f,  float (bounds.getY()), bounds.getBottom() - tickHeight)), tickWidth, tickHeight, juce::Justification::right, 1);
            g.drawFittedText (slider.getTextFromValue (slider.proportionOfLengthToValue (1.0f)),   xRight, int (bounds.getBottom() - tickHeight), tickWidth, tickHeight, juce::Justification::right, 1);

            bounds.removeFromTop (tickHeight + 4.0f);
            bounds.reduce (tickWidth, 0.0f);
        }

        radius = juce::jmin (bounds.getWidth() / 2.0f, bounds.getHeight() / 2.0f);
        centre = bounds.getCentre();

        if (radius > 50.0f)
        {
            for (int i = 0; i < 9; ++i)
            {
                const auto angle = juce::jmap (i / 8.0f, rotaryStartAngle, rotaryEndAngle);
                const auto point = centre.getPointOnCircumference (radius - 2.0f, angle);
                g.fillEllipse (point.getX() - 3, point.getY() - 3, 6, 6);
            }
            radius -= 10.0f;
        }

        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = juce::jmin (4.0f, radius * 0.5f);
        auto arcRadius  = radius - lineW;

        juce::Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     rotaryStartAngle,
                                     rotaryEndAngle,
                                     true);

        g.setColour (outline.darker());
        g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::butt));

        auto knobRadius = std:: max (radius - 3.0f * lineW, 10.0f);
        {
            juce::Graphics::ScopedSaveState saved (g);
            if (slider.isEnabled())
            {
                juce::ColourGradient fillGradient (outline, centre.getX() + lineW * 2.0f, centre.getY() - lineW * 4.0f, fill, centre.getX() + knobRadius, centre.getY() + knobRadius, true);
                g.setGradientFill (fillGradient);
            }
            g.fillEllipse (centre.getX() - knobRadius, centre.getY() - knobRadius, knobRadius * 2.0f, knobRadius * 2.0f);
        }

        knobRadius = std:: max (knobRadius - 4.0f, 10.0f);
        g.setColour (outline.brighter());
        g.drawEllipse (centre.getX() - knobRadius, centre.getY() - knobRadius, knobRadius * 2.0f, knobRadius * 2.0f, 2.0f);

        juce::Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::butt));
    }

    void drawComboBox (juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override
    {
        auto background = box.findColour (juce::ComboBox::backgroundColourId);

        if (dynamic_cast<juce::ChoicePropertyComponent*> (box.getParentComponent()) == nullptr)
        {
            g.setColour (background);
            g.fillRoundedRectangle (juce::Rectangle<float> (0.0f, 0.0f, float (width), float (height)), 4.0f);

            g.setColour (box.findColour (juce::ComboBox::outlineColourId));
            g.drawRoundedRectangle (juce::Rectangle<float> (0.0f, 0.0f, float (width), float (height)), 4.0f, 1.5f);
        }
    }

    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override
    {
        label.setFont (label.getFont().withHeight (box.getHeight() * 0.75f));
        label.setBounds (2, 2, box.getWidth() - 4, box.getHeight() - 4);
    }

    void drawTabButton (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown) override
    {
        auto activeArea = button.getActiveArea();

        const auto orientation = button.getTabbedButtonBar().getOrientation();
        const auto gradientEdge = 2.0f;

        juce::ColourGradient gradient (button.getTabBackgroundColour(), 0, 0, button.findColour (isMouseOver ? juce::TabbedButtonBar::tabOutlineColourId : juce::TabbedButtonBar::frontOutlineColourId), 0, 0, false);
        switch (orientation)
        {
            case juce::TabbedButtonBar::TabsAtTop:
                gradient.point1.setXY (activeArea.getX(), activeArea.getBottom() - gradientEdge);
                gradient.point2.setXY (activeArea.getX(), activeArea.getY() + gradientEdge);
                break;
            case juce::TabbedButtonBar::TabsAtBottom:
                gradient.point1.setXY (activeArea.getX(), activeArea.getY() + gradientEdge);
                gradient.point2.setXY (activeArea.getX(), activeArea.getBottom() - gradientEdge);
                break;
            case juce::TabbedButtonBar::TabsAtLeft:
                gradient.point1.setXY (activeArea.getRight() - gradientEdge, activeArea.getY());
                gradient.point2.setXY (activeArea.getX() + gradientEdge, activeArea.getY());
                break;
            case juce::TabbedButtonBar::TabsAtRight:
                gradient.point1.setXY (activeArea.getX() + gradientEdge, activeArea.getY());
                gradient.point2.setXY (activeArea.getRight() - gradientEdge, activeArea.getY());
                break;
        }

        g.setGradientFill (gradient);
        g.fillRect (activeArea);

        g.setColour (button.findColour (juce::TabbedButtonBar::outlineColourId));
        g.drawRect (activeArea);

        g.setColour (button.findColour (isMouseOver ? juce::TabbedButtonBar::tabTextColourId : juce::TabbedButtonBar::frontOutlineColourId));
        g.setFont (juce::Font (14.0f, juce::Font::plain));
        g.drawText (button.getButtonText(), activeArea, juce::Justification::centred);
    }
};

} // namespace MacielGUI
