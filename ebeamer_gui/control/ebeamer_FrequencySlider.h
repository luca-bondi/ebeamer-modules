/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

class JUCE_API FrequencySlider  : public SliderCC
{
public:
    FrequencySlider() {};

    double getValueFromText(const String &text) override {

        auto hzText = text.upToFirstOccurrenceOf("Hz", false, false).trim();
        auto hzVal = roundToInt(hzText.getDoubleValue());
        return hzVal;
    }

    String getTextFromValue(double value) override {
        std::ostringstream valueString;
        valueString << roundToInt(value) << " Hz";
        return valueString.str();
    }


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencySlider)
};

} /* end namespace juce */
