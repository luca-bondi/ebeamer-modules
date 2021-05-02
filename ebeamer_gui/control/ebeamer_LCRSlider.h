/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

class JUCE_API LCRSlider  : public SliderCC
{
public:
    LCRSlider() {};

    double getValueFromText(const String &text) override {

        if (text.startsWithIgnoreCase("C") || text.startsWithIgnoreCase("0")) {
            return 0;
        }

        float sign = 1;
        if (text.endsWithIgnoreCase("L")) {
            sign = -1;
        }

        String valueText = text.upToFirstOccurrenceOf("%", false, false).trim();
        double val = valueText.getDoubleValue() / 100.;
        return sign * val;
    }

    String getTextFromValue(double value) override {
        jassert(value >= -1 && value <= 1);
        std::ostringstream valueString;
        if (abs(value) < 0.01) {
            valueString << "C";
        } else if (value < 0) {
            valueString << roundToInt(abs(value) * 100) << " % L";
        } else {
            valueString << roundToInt((value) * 100) << " % R";
        }

        return valueString.str();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LCRSlider)
};

}  /* end namespace juce */

