/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

ConfigComboBox::ConfigComboBox(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.attachToComponent(&combo, true);
    combo.addItemList(micConfigLabels, 10);
    combo.addListener(this);
    combo.setSelectedItemIndex(0);
    addAndMakeVisible(combo);
    
}

ConfigComboBox::~ConfigComboBox(){
    
}

int ConfigComboBox::getMinWidth() const{
    return labelWidth+contentWidth;
}

void ConfigComboBox::init(Value v){
    combo.setSelectedItemIndex(v.getValue(),dontSendNotification);
    value = Value(v);
    value.addListener(this);
}

void ConfigComboBox::paint(Graphics &){
    
}

void ConfigComboBox::resized(){
    auto area = getLocalBounds();
    area.removeFromLeft(labelWidth);
    combo.setBounds(area);
}

void ConfigComboBox::comboBoxChanged(ComboBox *cb){
    value.setValue(cb->getSelectedItemIndex());
}

void ConfigComboBox::valueChanged(Value& v){
    combo.setSelectedItemIndex(v.getValue(),dontSendNotification);
}

} /* end namespace juce */
