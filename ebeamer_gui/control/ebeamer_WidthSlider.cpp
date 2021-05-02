/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

WidthSlider::WidthSlider(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&slider, true);
    slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider.setRange(minVal,maxVal,stepVal);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
}

WidthSlider::~WidthSlider(){
    
}

void WidthSlider::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    slider.enableMidi(cb,identifier.toString());
}

void WidthSlider::setLabelVisible(bool v){
    label.setVisible(v);
}

void WidthSlider::setTextBoxPosition(Slider::TextEntryBoxPosition pos){
    textBoxPos = pos;
    slider.setTextBoxStyle(pos, false, textBoxWidth, textBoxHeight);
    slider.setTextBoxIsEditable(textBoxEditable);
}

int WidthSlider::getMinWidth() const{
    return labelWidth+contentWidth;
}

void WidthSlider::init(Value v,  const Colour& c, bool editable){
    
    slider.setValue(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
    
    textBoxEditable = editable;
    slider.setTextBoxIsEditable(textBoxEditable);
    
    slider.setColour(Slider::thumbColourId, c);
    
}

void WidthSlider::paint(Graphics &){
    
}

void WidthSlider::resized(){
    auto area = getLocalBounds();
    
    if (label.isVisible())
        area.removeFromLeft(labelWidth);
    
    slider.setBounds(area);
}

void WidthSlider::sliderValueChanged(Slider *s){
    value.setValue(float(var(s->getValue())));
}

void WidthSlider::valueChanged(Value& v){
    slider.setValue(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
