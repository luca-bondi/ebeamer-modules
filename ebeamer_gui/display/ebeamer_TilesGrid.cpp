/*
 Acoustic scene components
 
 Authors:
 Matteo Scerbo (matteo.scerbo@mail.polimi.it)
 Luca Bondi (luca.bondi@polimi.it)
 */

namespace juce {

TilesGrid::TilesGrid(){
    
    const float ledStep = -GREEN_LT/(linearArrayNumLedsPerDirection-1); //dB
    const float redLowerThreshold  = RED_LT;
    
    th.clear();
    for (auto ledIdx = linearArrayNumLedsPerDirection - 1; ledIdx >= 0; --ledIdx) {
        auto ledThDb = ledIdx == (linearArrayNumLedsPerDirection - 1) ? redLowerThreshold : -((linearArrayNumLedsPerDirection - 1 - ledIdx) * ledStep);
        th.push_back(ledThDb);
    }
    
    energy.resize(1,std::vector<float>(15));
    
}

TilesGrid::~TilesGrid(){
    
}


void TilesGrid::init(Value frontFacingVal, Value configVal,  Value energyVal){
    
    
    frontFacing = frontFacingVal.getValue();
    valueFrontFacing = Value(frontFacingVal);
    valueFrontFacing.addListener(this);
    
    config = (MicConfig)int(configVal.getValue());
    valueConfig = Value(configVal);
    valueConfig.addListener(this);
    
    setEnergy(energyVal);
    valueEnergy = Value(energyVal);
    valueEnergy.addListener(this);
    
}

void TilesGrid::reset(){
    
    const uint8 numRows = (uint8)energy.size();
    const uint8 numCols = (uint8)energy[0].size();
    MemoryBlock mb(2+numRows*numCols*sizeof(float));
    float* data = (float*)((char*)mb.getData()+2);
    mb[0] = numRows;
    mb[1] = numCols;
    for (auto idx=0;idx<numRows*numCols;idx++)
        data[idx] = -100;
    setEnergy(Value(mb));
    repaint();
}


void TilesGrid::paint(Graphics &){
    
}

void TilesGrid::resized(){

    area = getLocalBounds();
    
    makeLayout();
    
    AffineTransform transf;
    
    if (frontFacing){
        if (isLinearArray(config)){
            transf = AffineTransform::rotation(pi, area.getWidth()/2, area.getHeight()/2);
        }else{
            transf = AffineTransform::verticalFlip(area.getHeight()).rotation(pi, area.getWidth()/2, area.getHeight()/2);
        }
    }
    
    for (int rowIdx = 0; rowIdx < tiles.size(); rowIdx++) {
        for (int colIdx = 0; colIdx < tiles[rowIdx].size(); colIdx++) {
            {
                Path path;
                path.startNewSubPath(vertices[rowIdx][colIdx]);
                path.lineTo(vertices[rowIdx + 1][colIdx]);
                path.lineTo(vertices[rowIdx + 1][colIdx + 1]);
                path.lineTo(vertices[rowIdx][colIdx + 1]);
                path.closeSubPath();
                
                path.applyTransform(transf);
                
                tiles[rowIdx][colIdx]->setPath(path);
            }
            
            Colour baseCol;
            if (isLinearArray(config)){
                baseCol = SingleChannelLedBar::dbToColour(-100,th[rowIdx]);
            }else{
                baseCol = MultiChannelLedBar::dbToColor(0);
            }
            tiles[rowIdx][colIdx]->setColour(baseCol);
            
            tiles[rowIdx][colIdx]->setBounds(area);
            
        }
    }
    
    for (auto &&row : energy)
        for (auto &&v : row)
            v = -100;

}

void TilesGrid::makeLayout() {
    
    vertices.clear();
    tiles.clear();
    
    if (isLinearArray(config)){
        vertices.resize(linearArrayNumLedsPerDirection+1, std::vector<juce::Point<float>>(energy[0].size()+1));
        
        float angle_diff = MathConstants<float>::pi / energy[0].size();
        
        for (int rowIdx = 0; rowIdx <= linearArrayNumLedsPerDirection; rowIdx++) {
            
            const float radius = jmin(area.getHeight(),area.getWidth()/2) * (1 - (exp((float) rowIdx / linearArrayNumLedsPerDirection) - 1) / (exp(1) - 1));
            
            for (int colIdx = 0; colIdx <= energy[0].size(); colIdx++) {
                const float angle = colIdx * angle_diff;
                
                vertices[rowIdx][colIdx].setX(area.getWidth() / 2 - radius * cos(angle));
                vertices[rowIdx][colIdx].setY(area.getHeight() - radius * sin(angle));
                
            }
        }
        
    }else{
        vertices.resize(energy.size()+1, std::vector<juce::Point<float>>(energy[0].size()+1));
        
        const float deltaY = float(area.getHeight()) / energy.size();
        const float deltaX = float(area.getWidth()) / energy[0].size();
        
        for (int rowIdx = 0; rowIdx <= energy.size(); rowIdx++) {
            for (int colIdx = 0; colIdx <= energy[0].size(); colIdx++) {
                vertices[rowIdx][colIdx].setY(rowIdx*deltaY);
                vertices[rowIdx][colIdx].setX(colIdx*deltaX);
            }
        }
        
    }
    
    tiles.resize(vertices.size()-1);
    for (auto &tilesRow : tiles){
        tilesRow.resize(energy[0].size());
        for (auto &tile :tilesRow){
            tile = std::make_unique<Tile>();
            addAndMakeVisible(*tile);
        }
    }
    
}

void TilesGrid::valueChanged(Value& v){
    
    if (v.refersToSameSourceAs(valueFrontFacing)){
        frontFacing = bool(v.getValue());
        resized();
    }else if (v.refersToSameSourceAs(valueConfig)){
        config = (MicConfig)int(v.getValue());
        resized();
    }else if (v.refersToSameSourceAs(valueEnergy)){
        setEnergy(v);
        repaint();
    }
}

void TilesGrid::setEnergy(const Value& v){
    
    const MemoryBlock mb = *(v.getValue().getBinaryData());
    const float* data = (float*)((char*)mb.getData()+2);
    const int numRows = mb[0];
    const int numCols = mb[1];
    
    if ((energy.size() != numRows) || (energy[0].size() != numCols)){
        energy.clear();
        energy.resize(numRows,std::vector<float>(numCols));
        resized();
    }
    
    for (auto rowIdx=0; rowIdx < numRows; rowIdx++){
        for (auto colIdx=0; colIdx < numCols; colIdx++){
            const float v = *(data + colIdx*numRows + rowIdx); //F-ordered matrix, Eigen format
            energy[rowIdx][colIdx] = v;
            if (isLinearArray(config)){
                for (auto tileRowIdx = 0; tileRowIdx < linearArrayNumLedsPerDirection; tileRowIdx++)
                    tiles[tileRowIdx][colIdx]->setColour(SingleChannelLedBar::dbToColour(v,th[tileRowIdx]));
            }else{
                tiles[rowIdx][colIdx]->setColour(MultiChannelLedBar::dbToColor(v));
            }
        }
    }
    
}

} /* end namespace juce */
