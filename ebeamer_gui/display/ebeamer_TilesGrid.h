/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce {

class JUCE_API TilesGrid:
public Component,
private Value::Listener
{
    
public:
    
    TilesGrid();
    ~TilesGrid();
    
    void init(Value frontFacing, Value config, Value energy );
    void paint(Graphics &) override;
    
    void resized() override;
    
    void reset();
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TilesGrid)
    
    /* Values and parameters */
    Value valueFrontFacing,valueEnergy,valueConfig;
    
    void valueChanged (Value&) override;
    
    bool frontFacing = false;
    MicConfig config = ULA_1ESTICK;
    std::vector<std::vector<float>> energy;
    
    /* Graphic */
    Rectangle<int> area;
    
    std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
    std::vector<std::vector<juce::Point<float>>> vertices;
    std::vector<float> th;
        
    void makeLayout();
    
    void setEnergy(const Value& v);
    void setEnergy(const std::vector<float>& v, int numRows, int numCols);
    
    const int linearArrayNumLedsPerDirection = 7;
    
};

} /* end namespace juce */
