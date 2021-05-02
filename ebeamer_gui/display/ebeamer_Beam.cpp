/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce{


void Beam::init(Value frontFacingVal, Value configVal, Value steerXVal, Value steerYVal, Value widthVal, Value muteVal){
    
    frontFacing = frontFacingVal.getValue();
    valueFrontFacing = Value(frontFacingVal);
    valueFrontFacing.addListener(this);
    
    config = (MicConfig)int(configVal.getValue());
    valueConfig = Value(configVal);
    valueConfig.addListener(this);
    
    steerX = steerXVal.getValue();
    valueSteerX = Value(steerXVal);
    valueSteerX.addListener(this);
    
    steerY = steerYVal.getValue();
    valueSteerY = Value(steerYVal);
    valueSteerY.addListener(this);
    
    beamWidth = widthVal.getValue();
    valueWidth = Value(widthVal);
    valueWidth.addListener(this);
    
    mute = muteVal.getValue();
    valueMute = Value(muteVal);
    valueMute.addListener(this);
    
}

void Beam::resized(){
    area = getLocalBounds();
}

void Beam::paint(Graphics &g) {

    path.clear();
    
    
    if (isLinearArray(config)){
        const float positionX = steerX;
        
        const float width = (0.3 + 2.0 * (beamWidth)) * area.getHeight() / 5;
        const float length = jmin(area.getWidth(),2*area.getHeight())*0.99;
        path.startNewSubPath(0, 0);
        path.cubicTo(width, -length / 4, width, -length / 2, 0, -length / 2);
        path.cubicTo(-width, -length / 2, -width, -length / 4, 0, 0);
        path.closeSubPath();
        
        path.applyTransform(AffineTransform::rotation((pi / 2) * positionX));
        path.applyTransform(AffineTransform::translation(area.getWidth() / 2, area.getHeight()));
        
        if (frontFacing) {
            path.applyTransform(AffineTransform::verticalFlip(area.getHeight()));
        }
    }
    else{
        const float positionX = (steerX + 1)*area.getWidth()/2 ;
        const float positionY = area.getHeight() - ((steerY + 1)*area.getHeight()/2);
        const float width = (0.5 + 2.5 * (beamWidth)) * area.getWidth() / 10;
        
        path.startNewSubPath(0, 0);
        path.addEllipse(positionX-width/2, positionY-width/2, width, width);
    }
        
    if (!mute) {
        g.setColour(baseColour.brighter());
        g.setOpacity(0.4);
        g.fillPath(path);
    }
    
    g.setColour(baseColour);
    g.setOpacity(0.9);
    PathStrokeType strokeType(2);
    g.strokePath(path, strokeType);
}

void Beam::valueChanged(Value& v){
    
    if (v.refersToSameSourceAs(valueFrontFacing)){
        frontFacing = bool(v.getValue());
    }else if (v.refersToSameSourceAs(valueConfig)){
        config = (MicConfig)int(v.getValue());
    }else if (v.refersToSameSourceAs(valueSteerX)){
        steerX = float(v.getValue());
        repaint();
    }else if (v.refersToSameSourceAs(valueSteerY)){
        steerY = float(v.getValue());
        repaint();
    }else if (v.refersToSameSourceAs(valueWidth)){
        beamWidth = float(v.getValue());
        repaint();
    }else if (v.refersToSameSourceAs(valueMute)){
        mute = bool(v.getValue());
        repaint();
    }
}

}
