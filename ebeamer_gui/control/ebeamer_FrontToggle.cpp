/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

FrontToggle::FrontToggle(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&button, true);
    addAndMakeVisible(button);
    button.addListener(this);
}

FrontToggle::~FrontToggle(){
    
}

void FrontToggle::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    button.enableMidi(cb,identifier.toString());
}

int FrontToggle::getMinWidth() const{
    return labelWidth+contentWidth;
}

void FrontToggle::init(Value v){
    button.setToggleState(v.getValue(), dontSendNotification);
    value = Value(v);
    value.addListener(this);
}

void FrontToggle::paint(Graphics &){
    
}

void FrontToggle::resized(){
    auto area = getLocalBounds();
    area.removeFromLeft(labelWidth);
    button.setBounds(area);
}

void FrontToggle::buttonStateChanged(Button *b){
    auto toggleValue = bool(var(b->getToggleStateValue()));
    if (toggleValue != bool(value.getValue())){
        value.setValue(toggleValue);
    }
}

void FrontToggle::valueChanged(Value& v){
    button.setToggleState(v.getValue(), dontSendNotification);
}

} /* end namespace juce */
