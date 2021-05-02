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
class JUCE_API RoundLed : public Component {
public:
    
    RoundLed() {};
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    void setColour(const Colour&);
    
protected:
    
    Colour colour;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoundLed)
};

} /* end namespace juce */
