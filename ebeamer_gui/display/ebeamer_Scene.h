/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce{



//==============================================================================

class JUCE_API Scene :
public Component,
private Value::Listener
{
public:
    Scene();
    
    ~Scene() {};
    
    void init(Value frontFacing, Value config, Value energy, Value steerX1, Value steerY1, Value width1, Value mute1,  Value steerX2, Value steerY2, Value width2, Value mute2);
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    void setBeamColors(const std::vector<Colour> &colours);
    
    void reset();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Scene)
    
    Beam beams[2];
    TilesGrid grid;
    
    Rectangle<int> area;
    
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    
    int beamBeingDragged = -1;
    float dragStartX, dragStartY, originX, originY;
    
    /* Values and parameters */
    Value valueFrontFacing,valueConfig,valueSteerX1,valueSteerY1,valueSteerX2,valueSteerY2;
    void valueChanged (Value&) override;
    
    MicConfig config = ULA_1ESTICK;;
    bool frontFacing = false;
    
    
};

}
