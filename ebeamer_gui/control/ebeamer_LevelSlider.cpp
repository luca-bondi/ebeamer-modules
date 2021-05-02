/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

LevelSlider::LevelSlider(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&slider, true);
    slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    slider.setRange(minVal,maxVal,stepVal);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
}

LevelSlider::~LevelSlider(){
    
}

void LevelSlider::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    slider.enableMidi(cb,identifier.toString());
}

void LevelSlider::setLabelVisible(bool v){
    label.setVisible(v);
}

void LevelSlider::setTextBoxPosition(Slider::TextEntryBoxPosition pos){
    textBoxPos = pos;
    slider.setTextBoxStyle(pos, false, textBoxWidth, textBoxHeight);
    slider.setTextBoxIsEditable(textBoxEditable);
}

int LevelSlider::getMinWidth() const{
    return labelWidth+contentWidth;
}

void LevelSlider::init(Value v, const Colour& c, bool editable){
    
    slider.setValue(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
    
    textBoxEditable = editable;
    slider.setTextBoxIsEditable(textBoxEditable);
    
    slider.setColour(Slider::thumbColourId, c);
}

void LevelSlider::paint(Graphics &){
    
}

void LevelSlider::resized(){
    auto area = getLocalBounds();
    
    if (label.isVisible())
        area.removeFromLeft(labelWidth);
    
    slider.setBounds(area);
}

void LevelSlider::sliderValueChanged(Slider *s){
    value.setValue(float(var(s->getValue())));
}

void LevelSlider::valueChanged(Value& v){
    slider.setValue(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
