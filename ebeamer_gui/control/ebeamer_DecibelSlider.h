/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

#define DB_MINUS_INF -100.0


class DecibelSlider  : public SliderCC
{
public:
    DecibelSlider() {};

    double getValueFromText(const String &text) override {

        auto decibelText = text.upToFirstOccurrenceOf("dB", false, false).trim();

        return decibelText.equalsIgnoreCase("-INF") ? DB_MINUS_INF
                                                    : decibelText.getDoubleValue();  // [2]
    }

    String getTextFromValue(double value) override {
        return Decibels::toString(value, 1, DB_MINUS_INF);
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DecibelSlider)
};

} /* end namespace juce */
