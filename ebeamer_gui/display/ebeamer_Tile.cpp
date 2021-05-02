/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce{


void Tile::paint(Graphics &g) {
    
    g.setColour(tileColour);
    g.fillPath(path);
    
    g.setColour(Colours::black);
    PathStrokeType strokeType(pathStroke);
    g.strokePath(path, strokeType);
}


void Tile::setColour(const Colour &col) {
    tileColour = col;
}

void Tile::setPath(const Path& p) {
    path = p;
}

}
