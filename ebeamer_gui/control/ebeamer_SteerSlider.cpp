/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

SteerSlider::SteerSlider(){
    
    label.attachToComponent(&slider, true);
    slider.setRange(minVal,maxVal,stepVal);
    slider.addListener(this);
    addAndMakeVisible(slider);
    
}

SteerSlider::~SteerSlider(){
    
}

void SteerSlider::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    slider.enableMidi(cb,identifier.toString());
}

void SteerSlider::setLabelText(const String & t){
    label.setText(t, NotificationType::dontSendNotification);
    labelWidth = jmax(10*t.length(),20);
}

void SteerSlider::setLabelVisible(bool v){
    label.setVisible(v);
}

int SteerSlider::getMinWidth() const{
    return labelWidth+contentWidth;
}

void SteerSlider::init(Value v,  const Colour& c, bool editable, bool vertical){
    slider.setValue(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
    
    textBoxEditable = editable;
    slider.setTextBoxIsEditable(editable);
    
    slider.setColour(Slider::thumbColourId, c);
    
    if (vertical){
        slider.setSliderStyle(Slider::LinearVertical);
        slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxAbove, !textBoxEditable, textBoxWidth, textBoxHeight);
    }else{
        slider.setSliderStyle(Slider::LinearHorizontal);
        slider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxRight, !textBoxEditable, textBoxWidth, textBoxHeight);
    }
}

void SteerSlider::paint(Graphics &){
    
}

void SteerSlider::resized(){
    auto area = getLocalBounds();
    
    if (label.isVisible() && slider.getSliderStyle()==Slider::LinearHorizontal){
        area.removeFromLeft(labelWidth);
    }
    
    slider.setBounds(area);
}

void SteerSlider::sliderValueChanged(Slider *s){
    value.setValue(float(var(s->getValue())));
}

void SteerSlider::valueChanged(Value& v){
    slider.setValue(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
