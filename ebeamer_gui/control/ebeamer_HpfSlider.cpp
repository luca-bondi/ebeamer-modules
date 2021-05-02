/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

HpfSlider::HpfSlider(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&slider, true);
    slider.setSliderStyle(Slider::LinearHorizontal);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxRight, false, textBoxWidth, textBoxHeight);
    slider.setRange(minVal,maxVal,stepVal);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
}

HpfSlider::~HpfSlider(){
    
}

void HpfSlider::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    slider.enableMidi(cb,identifier.toString());
}

int HpfSlider::getMinWidth() const{
    return labelWidth+contentWidth;
}

void HpfSlider::init(Value v, bool editable){
    slider.setValue(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
    textBoxEditable = editable;
    slider.setTextBoxIsEditable(textBoxEditable);
}

void HpfSlider::paint(Graphics &){
    
}

void HpfSlider::resized(){
    auto area = getLocalBounds();
    area.removeFromLeft(labelWidth);
    slider.setBounds(area);
}

void HpfSlider::sliderValueChanged(Slider *s){
    value.setValue(float(var(s->getValue())));
}

void HpfSlider::valueChanged(Value& v){
    slider.setValue(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
