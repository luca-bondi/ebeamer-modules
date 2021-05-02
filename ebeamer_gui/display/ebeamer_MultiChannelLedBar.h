/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {
//==============================================================================
/*
*/
class JUCE_API MultiChannelLedBar:
public Component,
private Value::Listener
{
public:
    
    MultiChannelLedBar();
    
    ~MultiChannelLedBar() {};
    
    void init(Value);
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    void setHorizontal() { isHorizontal = true; };
    
    void setVertical() { isHorizontal = false; };
    
    static Colour dbToColor(float valDb);
    
    void setValues(const Array<float>&);
    
    void reset();
    
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MultiChannelLedBar)
    
    Value value;
    
    const float maxLedDistance = 100.;
    
    bool isHorizontal = true;
    
    std::vector<std::unique_ptr<RoundLed>> leds;
    Array<float> values = {0,0};
    
    void makeLayout();
    
    void valueChanged (Value&) override;
    
};

} /* end namespace juce */
