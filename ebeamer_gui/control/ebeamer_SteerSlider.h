/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API SteerSlider:
public Component,
private Slider::Listener,
private Value::Listener
{
    
public:
    
    SteerSlider();
    ~SteerSlider();
    
    void init(Value value, const Colour& colour, bool textBoxEditable, bool vertical);
    
    void setLabelText(const String &);
    
    void setLabelVisible(bool);
    
    void resized() override;
    
    void paint(Graphics &) override;
    
    int getMinWidth() const;
    
    void enableMidi(MidiCC::Callback*, const Identifier& identifier);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SteerSlider)
    
    Value value;
    
    int labelWidth = 0;
    const int contentWidth = 60;
    
    const float minVal = -1;
    const float maxVal = 1;
    const float stepVal = 0.01;
    
    const int textBoxWidth = 70;
    const int textBoxHeight = 20;
    
    Label label;
    SliderCC slider;
    
    void sliderValueChanged (Slider*) override;
    void valueChanged (Value&) override;
    
    bool textBoxEditable;
    
};

} /* end namespace juce */
