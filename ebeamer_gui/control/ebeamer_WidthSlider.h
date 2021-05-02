/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API WidthSlider:
public Component,
private Slider::Listener,
private Value::Listener
{
    
public:
    
    WidthSlider();
    ~WidthSlider();
    
    void init(Value, const Colour&, bool);
    
    void setLabelVisible(bool);
    
    void setTextBoxPosition(Slider::TextEntryBoxPosition);
    void setFakeTextBoxLineVisible(bool v);
    
    void resized() override;
    
    void paint(Graphics &) override;
    
    int getMinWidth() const;
    
    void enableMidi(MidiCC::Callback*, const Identifier& identifier);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WidthSlider)
    
    Value value;
    
    const String labelText = "WIDTH";
    
    const int labelWidth = 70;
    const int contentWidth = 90;
    
    const float minVal = 0;
    const float maxVal = 1;
    const float stepVal = 0.01;
    
    const int textBoxWidth = 70;
    const int textBoxHeight = 20;
    
    Label label;
    SliderCC slider;
    
    void sliderValueChanged (Slider*) override;
    void valueChanged (Value&) override;
    
    Slider::TextEntryBoxPosition textBoxPos;
    bool textBoxEditable;
    
};

} /* end namespace juce */
