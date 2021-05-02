/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API ActivityLed: public RoundLed {
    
public:
    
    ActivityLed(){};
    
    void setColours(const Colour& colour1_,const Colour& colour2_);
    
    void toggle();
    
private:
    
    Colour colour1, colour2;
    
};

} /* end namespace juce */
