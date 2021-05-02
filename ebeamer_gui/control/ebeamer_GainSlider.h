/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API GainSlider:
public Component,
private Slider::Listener,
private Value::Listener
{
    
public:
    
    GainSlider();
    ~GainSlider();
    
    void init(Value,bool);
    
    void resized() override;
    
    void paint(Graphics &) override;
    
    int getMinWidth() const;
    
    void enableMidi(MidiCC::Callback*, const Identifier& identifier);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSlider)
    
    Value value;
    bool textBoxEditable = true;
    
    const String labelText = "GAIN";
    
    const int labelWidth = 70;
    const int contentWidth = 100;
    
    const float minVal = MIN_GAIN;
    const float maxVal = MAX_GAIN;
    const float stepVal = 0.1;
    
    const int textBoxWidth = 70;
    const int textBoxHeight = 20;
    
    Label label;
    DecibelSlider slider;
    
    void sliderValueChanged (Slider*) override;
    void valueChanged (Value&) override;
    
    
};

} /* end namespace juce */
