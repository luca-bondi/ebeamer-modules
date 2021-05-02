/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

void RoundLed::paint(Graphics &g) {
    
    Rectangle<float> area = getLocalBounds().toFloat();
    auto side = area.getHeight() > area.getWidth() ? area.getWidth() : area.getHeight();
    auto ctr = area.getCentre();
    area = Rectangle<float>(side, side);
    area.setCentre(ctr);
    
    g.setColour(colour);
    g.fillEllipse(area);
}

void RoundLed::resized() {
    
}

void RoundLed::setColour(const Colour& newColour){
    colour = newColour;
    repaint();
}

} /* end namespace juce */
