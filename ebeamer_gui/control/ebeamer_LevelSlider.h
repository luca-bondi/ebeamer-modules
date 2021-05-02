/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API LevelSlider:
public Component,
private Slider::Listener,
private Value::Listener
{
    
public:
    
    LevelSlider();
    ~LevelSlider();
    
    void init(Value, const Colour&, bool);
    
    void setLabelVisible(bool);
    
    void setTextBoxPosition(Slider::TextEntryBoxPosition);
    
    void resized() override;
    
    void paint(Graphics &) override;
    
    int getMinWidth() const;
    
    void enableMidi(MidiCC::Callback*, const Identifier& identifier);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelSlider)
    
    Value value;
    
    const String labelText = "LEVEL";
    
    const int labelWidth = 70;
    const int contentWidth = 90;
    
    const float minVal = MIN_LEVEL;
    const float maxVal = MAX_LEVEL;
    const float stepVal = 0.1;
    
    const int textBoxWidth = 70;
    const int textBoxHeight = 20;
    
    Label label;
    DecibelSlider slider;
    
    void sliderValueChanged (Slider*) override;
    void valueChanged (Value&) override;
    
    Slider::TextEntryBoxPosition textBoxPos;
    bool textBoxEditable;
    
};

} /* end namespace juce */
