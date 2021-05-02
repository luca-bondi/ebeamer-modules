/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {


MultiChannelLedBar::MultiChannelLedBar(){
    makeLayout();
}

void MultiChannelLedBar::makeLayout() {
    removeAllChildren();
    leds.clear();
    auto num = values.size();
    for (auto ledIdx = 0; ledIdx < num; ++ledIdx) {
        leds.push_back(std::make_unique<RoundLed>());
        leds[ledIdx]->setColour(Colours::grey);
        addAndMakeVisible(leds[ledIdx].get());
    }
    resized();
}

void MultiChannelLedBar::setValues(const Array<float>& newValues){
    if (values.size() != newValues.size()){
        values = newValues;
        makeLayout();
    }else{
        values = newValues;
    }
    for (auto ledIdx = 0; ledIdx < leds.size(); ++ledIdx)
        leds[ledIdx]->setColour(dbToColor(Decibels::gainToDecibels(values[ledIdx])));
}

void MultiChannelLedBar::init(Value v){
    value = Value(v);
    value.addListener(this);
}

void MultiChannelLedBar::paint(Graphics &) {
    
}

void MultiChannelLedBar::resized() {
    
    auto num = values.size();
    Rectangle<int> area = getLocalBounds();
    
    float step = jmin<float>(isHorizontal ? floor(area.getWidth() / num) : floor(area.getHeight() / num),maxLedDistance);
    float otherDim = isHorizontal ? area.getHeight() : area.getWidth();
    otherDim = jmin(otherDim, step - 1);
    
    const auto areaCtr = area.getCentre();
    
    // Re-center the area
    if (isHorizontal) {
        area.setWidth(step * num);
        area.setHeight(otherDim);
    } else {
        area.setHeight(step * num);
        area.setWidth(otherDim);
    }
    area.setCentre(areaCtr);
    
    for (auto ledIdx = 0; ledIdx < num; ++ledIdx) {
        Rectangle<int> ledArea = isHorizontal ? area.removeFromLeft(step) : area.removeFromTop(step);
        leds[ledIdx]->setBounds(ledArea);
    }
    
}

Colour MultiChannelLedBar::dbToColor(float valDb){
    Colour col;
    if (valDb > RED_LT) {
        col = Colours::red;
    } else if (valDb > ORANGE_LT) {
        col = Colours::orange;
    } else if (valDb > YELLOW_LT) {
        col = Colours::yellow;
    } else if (valDb > GREEN_LT) {
        col = Colours::lightgreen;
    } else {
        col = Colours::darkgreen;
    }
    return col;
}

void MultiChannelLedBar::reset(){
    std::vector<float> zeros(values.size(),0);
    setValues(Array<float>(zeros.data(),(int)zeros.size()));
}

void MultiChannelLedBar::valueChanged(Value& v){
    
    const MemoryBlock mb = *(v.getValue().getBinaryData());
    const float* data = (float*)((char*)mb.getData()+2);
    const int numEl = mb[0]*mb[1];
    
    Array<float> array(data,numEl);
    
    setValues(array);
}

} /* end namespace juce */
