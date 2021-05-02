/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce{



//==============================================================================

class JUCE_API Beam :
public Component,
private Value::Listener
{
public:
    Beam() {};
    
    ~Beam() {};
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    void setBaseColor(Colour colour) { baseColour = colour; }
    
    void init(Value frontFacing, Value config, Value steerX, Value steerY, Value width, Value mute);
    
    const Path& getPath(){
        return path;
    };
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Beam)
    
    Rectangle<int> area;
    Path path;
    
    Colour baseColour = Colours::lightblue;
    
    /* Values and parameters */
    Value valueFrontFacing,valueConfig,valueSteerX,valueSteerY,valueWidth,valueMute;
    
    void valueChanged (Value&) override;
    
    MicConfig config = ULA_1ESTICK;
    float steerX = 0;
    float steerY = 0;
    float beamWidth = 0;
    bool frontFacing = false;
    bool mute = false;
    
};

}
