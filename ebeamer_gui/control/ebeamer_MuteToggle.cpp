/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

MuteButton::MuteButton(){
    
    label.setText(labelText, NotificationType::dontSendNotification);
    label.setJustificationType(Justification::centredRight);
    addAndMakeVisible(label);
    addAndMakeVisible(button);
    button.addListener(this);
    
    getLookAndFeel().setColour(TextToggleButton::buttonOnColourId, Colours::darkred);
    
}

MuteButton::~MuteButton(){
    
}

void MuteButton::enableMidi(MidiCC::Callback* cb,const Identifier& identifier){
    button.enableMidi(cb,identifier.toString());
}

void MuteButton::setLabelVisible(bool v){
    label.setVisible(v);
}

void MuteButton::setFakeTextBoxLineVisible(bool v){
    fakeTextBoxLineVisible = v;
}

int MuteButton::getMinWidth() const{
    return labelWidth+contentWidth+textBoxWidth;
}

void MuteButton::init(Value v,const String& t){
    button.setToggleState(v.getValue(), dontSendNotification);
    value = Value(v);
    value.addListener(this);
    
    button.setButtonText(t);
}

void MuteButton::setFakeTextBoxPosition(Slider::TextEntryBoxPosition pos){
    textBoxPos = pos;
}

void MuteButton::paint(Graphics & g){
    if (fakeTextBoxLineVisible){
        auto startX = fakeTextBoxArea.getX() + fakeTextBoxLineMargin;
        auto endX = fakeTextBoxArea.getX() + fakeTextBoxArea.getWidth() - fakeTextBoxLineMargin;
        auto y = fakeTextBoxArea.getY() + fakeTextBoxArea.getHeight() / 2;
        g.setColour(Colours::grey);
        g.drawLine(startX, y, endX, y, fakeTextBoxLineThickness);
    }
}

void MuteButton::resized(){
    auto area = getLocalBounds();
    
    if (label.isVisible()){
        label.setBounds(area.removeFromLeft(labelWidth));
    }
    
    auto buttonSize = jmin(area.getWidth(),area.getHeight());
    Rectangle<int> buttonArea;
    
    if (textBoxPos == Slider::TextBoxRight){
        fakeTextBoxArea = area.removeFromRight(textBoxWidth);
        buttonArea = area.withSizeKeepingCentre(buttonSize, buttonSize);
        fakeTextBoxArea.setLeft(buttonArea.getX()+buttonArea.getWidth());
    }else if(textBoxPos == Slider::TextBoxLeft){
        fakeTextBoxArea = area.removeFromLeft(textBoxWidth);
        buttonArea = area.withSizeKeepingCentre(buttonSize, buttonSize);
        fakeTextBoxArea.setRight(buttonArea.getX());
    }
    
    button.setBounds(buttonArea);
    
}

void MuteButton::buttonStateChanged(Button *b){
    auto toggleValue = bool(var(b->getToggleStateValue()));
    if (toggleValue != bool(value.getValue())){
        value.setValue(toggleValue);
    }
}

void MuteButton::valueChanged(Value& v){
    button.setToggleState(v.getValue(), dontSendNotification);
}

} /* end namespace juce */
