/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

void ActivityLed::setColours(const Colour& colour1_,const Colour& colour2_){
    colour1 = colour1_;
    colour2 = colour2_;
    
    setColour(colour1);
}


void ActivityLed::toggle(){
    
    if (colour == colour1){
        setColour(colour2);
    }else{
        setColour(colour1);
    }
}

} /* end namespace juce */
