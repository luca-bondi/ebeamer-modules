/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

PanSlider::PanSlider(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&slider, true);
    slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider.setRange(minVal,maxVal,stepVal);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
}

PanSlider::~PanSlider(){
    
}

void PanSlider::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    slider.enableMidi(cb,identifier.toString());
}

void PanSlider::setLabelVisible(bool v){
    label.setVisible(v);
}

void PanSlider::setTextBoxPosition(Slider::TextEntryBoxPosition pos){
    textBoxPos = pos;
    slider.setTextBoxStyle(pos, false, textBoxWidth, textBoxHeight);
    slider.setTextBoxIsEditable(textBoxEditable);
}

int PanSlider::getMinWidth() const{
    return labelWidth+contentWidth;
}

void PanSlider::init(Value v, const Colour& c, bool editable){
    
    slider.setValue(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
    
    textBoxEditable = editable;
    slider.setTextBoxIsEditable(textBoxEditable);
    
    slider.setColour(Slider::thumbColourId, c);
}

void PanSlider::paint(Graphics &){
    
}

void PanSlider::resized(){
    auto area = getLocalBounds();
    
    if (label.isVisible())
        area.removeFromLeft(labelWidth);
    
    slider.setBounds(area);
}

void PanSlider::sliderValueChanged(Slider *s){
    value.setValue(float(var(s->getValue())));
}

void PanSlider::valueChanged(Value& v){
    slider.setValue(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
