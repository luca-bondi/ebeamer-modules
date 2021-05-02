/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

CpuLoad::CpuLoad(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&content, true);
    content.setText("0 %", NotificationType::dontSendNotification);
    content.setJustificationType(Justification::right);
    addAndMakeVisible(content);
}

CpuLoad::~CpuLoad(){
    
}

int CpuLoad::getMinWidth() const{
    return labelWidth+contentWidth;
}

void CpuLoad::init(Value v){
    value = Value(v);
    value.addListener(this);
}

void CpuLoad::paint(Graphics &){
    
}

void CpuLoad::resized(){
    auto area = getLocalBounds();
    area.removeFromLeft(labelWidth);
    content.setBounds(area);
}

void CpuLoad::valueChanged(Value& v){
    content.setText(String(roundToInt(float(var(v))*100)) + "%", NotificationType::dontSendNotification);
}

} /* end namespace juce */
