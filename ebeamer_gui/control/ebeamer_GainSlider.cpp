/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

GainSlider::GainSlider(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&slider, true);
    slider.setSliderStyle(Slider::LinearHorizontal);
    slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxRight, false, textBoxWidth, textBoxHeight);
    slider.setRange(minVal,maxVal,stepVal);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
}

GainSlider::~GainSlider(){
    
}

void GainSlider::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    slider.enableMidi(cb,identifier.toString());
}


int GainSlider::getMinWidth() const{
    return labelWidth+contentWidth;
}

void GainSlider::init(Value v,bool editable){
    slider.setValue(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
    textBoxEditable = editable;
    slider.setTextBoxIsEditable(textBoxEditable);
}

void GainSlider::paint(Graphics &){
    
}

void GainSlider::resized(){
    auto area = getLocalBounds();
    area.removeFromLeft(labelWidth);
    slider.setBounds(area);
}

void GainSlider::sliderValueChanged(Slider *s){
    value.setValue(float(var(s->getValue())));
}

void GainSlider::valueChanged(Value& v){
    slider.setValue(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
