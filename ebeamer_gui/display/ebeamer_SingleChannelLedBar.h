/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API SingleChannelLedBar:
public Component,
private Value::Listener
{
public:
    
    SingleChannelLedBar(size_t numLeds = 7, bool isHorizontal = false);
    
    ~SingleChannelLedBar() {};
    
    void init(Value);
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    static Colour dbToColour(float valDb, float thDb);
    
    void setValue(float);
    
    void reset();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SingleChannelLedBar)
    
    Value value;
    
    bool isHorizontal;
    
    std::vector<float> th;
    std::vector<std::unique_ptr<RoundLed>> leds;
    
    void valueChanged (Value&) override;
    
};

} /* end namespace juce */
