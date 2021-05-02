/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce{


Scene::Scene() {
    addAndMakeVisible(grid);
    for (auto &b:beams){
        addAndMakeVisible(b);
        b.addMouseListener(this, true);
    }
}

void Scene::init(Value frontFacingVal, Value configVal, Value energyVal, Value steerX1Val, Value steerY1Val, Value width1Val, Value mute1Val,  Value steerX2Val, Value steerY2Val, Value width2Val, Value mute2Val){
    
    frontFacing = frontFacingVal.getValue();
    valueFrontFacing = Value(frontFacingVal);
    valueFrontFacing.addListener(this);
    
    config = (MicConfig)int(configVal.getValue());
    valueConfig = Value(configVal);
    valueConfig.addListener(this);
    
    valueSteerX1 = Value(steerX1Val);
    valueSteerX1.addListener(this);
    
    valueSteerY1 = Value(steerY1Val);
    valueSteerY1.addListener(this);
    
    valueSteerX2 = Value(steerX2Val);
    valueSteerX2.addListener(this);
    
    valueSteerY2 = Value(steerY2Val);
    valueSteerY2.addListener(this);
    
    grid.init(frontFacingVal, configVal, energyVal);
    beams[0].init(frontFacingVal, configVal, steerX1Val, steerY1Val, width1Val, mute1Val);
    beams[1].init(frontFacingVal, configVal, steerX2Val, steerY2Val, width2Val, mute2Val);

    resized();
    repaint();
}

void Scene::paint(Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void Scene::resized() {
    area = getLocalBounds();
    
    originX = area.getCentreX();
    
    if (frontFacing){
        originY = area.getY();
    }else{
        originY = area.getBottom();
    }

    
    if (grid.getBounds() == area){
        grid.resized();
    }else{
        grid.setBounds(area);
    }
    
    for (auto &b: beams)
        b.setBounds(area);
}

void Scene::reset(){
    grid.reset();
}

void Scene::setBeamColors(const std::vector<Colour> &colours) {
    jassert(colours.size() == 2);
    for (auto beamIdx = 0; beamIdx < 2; ++beamIdx) {
        beams[beamIdx].setBaseColor(colours[beamIdx]);
    }
}

void Scene::mouseDown (const MouseEvent& e){
    beamBeingDragged = -1;
    for (int idx = 0; idx < 2; idx++){
        if (beams[idx].getPath().contains(e.getMouseDownPosition().toFloat())){
            beamBeingDragged = idx;
            break;
        }
    }
    switch (beamBeingDragged){
        case 0:
            dragStartX = valueSteerX1.getValue();
            dragStartY = valueSteerY1.getValue();
            break;
        case 1:
            dragStartX = valueSteerX2.getValue();
            dragStartY = valueSteerY2.getValue();
            break;
    }
}

void Scene::mouseDrag (const MouseEvent& e){
    if (beamBeingDragged >= 0){
        if (isLinearArray(config)){
            const float posX = e.getPosition().getX();
            const float posY = e.getPosition().getY();
            float dragCurrentAngle;
            if (frontFacing){
                dragCurrentAngle = atan2((posX-originX),(posY-originY));
            }else{
                dragCurrentAngle = atan2((posX-originX),-(posY-originY));
            }
            const float newX = jlimit(-1.f,1.f,dragCurrentAngle/(pi/2.f));
            switch (beamBeingDragged){
                case 0:
                    valueSteerX1.setValue(newX);
                    break;
                case 1:
                    valueSteerX2.setValue(newX);
                    break;
            }
        }else{
            const float deltaX = float(e.getDistanceFromDragStartX())/area.getWidth()*2;
            const float deltaY = float(-e.getDistanceFromDragStartY())/area.getHeight()*2;
            const float newX = jlimit(-1.f,1.f,dragStartX + deltaX);
            const float newY = jlimit(-1.f,1.f,dragStartY + deltaY);
            switch (beamBeingDragged){
                case 0:
                    valueSteerX1.setValue(newX);
                    valueSteerY1.setValue(newY);
                    break;
                case 1:
                    valueSteerX2.setValue(newX);
                    valueSteerY2.setValue(newY);
                    break;
                default:
                    jassertfalse;
            }
        }
    }
}

void Scene::mouseUp (const MouseEvent& e){
    beamBeingDragged = -1;
}

void Scene::valueChanged(Value& v){
    
    if (v.refersToSameSourceAs(valueFrontFacing)){
        frontFacing = bool(v.getValue());
        resized();
    }else if (v.refersToSameSourceAs(valueConfig)){
        config = (MicConfig)int(v.getValue());
        resized();
    }else if (v.refersToSameSourceAs(valueSteerX1) || v.refersToSameSourceAs(valueSteerX2) || v.refersToSameSourceAs(valueSteerY1) || v.refersToSameSourceAs(valueSteerY2)){
    }
}

}
