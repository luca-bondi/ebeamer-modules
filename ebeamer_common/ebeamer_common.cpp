/*
  ==============================================================================

 Ebeamer common module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

#ifdef JUCE_EBEAMER_COMMON_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

#include "ebeamer_common.h"

#include "common/ebeamer_MicConfig.cpp"
#include "common/ebeamer_ValueTreeFile.cpp"

namespace juce {

void initValueTreeParameters(ValueTree& valueTree){
    valueTree.setProperty(configIdentifier,ULA_1ESTICK,nullptr);
    valueTree.setProperty(frontIdentifier,false,nullptr);
    valueTree.setProperty(cpuIdentifier,0,nullptr);
    valueTree.setProperty(hpfIdentifier,DEFAULT_HPF,nullptr);
    valueTree.setProperty(gainIdentifier,DEFAULT_GAIN,nullptr);
    valueTree.setProperty(steerX1Identifier,-0.2,nullptr);
    valueTree.setProperty(steerX2Identifier,0.2,nullptr);
    valueTree.setProperty(steerY1Identifier,-0.2,nullptr);
    valueTree.setProperty(steerY2Identifier,0.2,nullptr);
    valueTree.setProperty(width1Identifier,0.2,nullptr);
    valueTree.setProperty(width2Identifier,0.4,nullptr);
    valueTree.setProperty(pan1Identifier,-0.5,nullptr);
    valueTree.setProperty(pan2Identifier,0.5,nullptr);
    valueTree.setProperty(level1Identifier,-4,nullptr);
    valueTree.setProperty(level2Identifier,4,nullptr);
    valueTree.setProperty(mute1Identifier,false,nullptr);
    valueTree.setProperty(mute2Identifier,true,nullptr);
    
    MemoryBlock inMetersInit(2+4*sizeof(float));
    inMetersInit[0] = 1;
    inMetersInit[1] = 4;
    valueTree.setProperty(inMetersIdentifier,inMetersInit,nullptr);
    valueTree.setProperty(outMeter1Identifier,0,nullptr);
    valueTree.setProperty(outMeter2Identifier,0,nullptr);
    
    MemoryBlock energyInit(2+9*sizeof(float));
    energyInit[0] = 1;
    energyInit[1] = 9;
    valueTree.setProperty(energyIdentifier,energyInit,nullptr);
}

}
