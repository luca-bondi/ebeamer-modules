/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce{

class JUCE_API Tile : public Component {
public:
    
    Tile() {};
    ~Tile() {};
    
    void paint(Graphics &) override;
    void resized() override {};
    
    void setColour(const Colour &col);
    void setPath(const Path &);
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Tile)
    
    Path path;
    Colour tileColour;
    
    const float pathStroke = 0.5f;
    
};

}
