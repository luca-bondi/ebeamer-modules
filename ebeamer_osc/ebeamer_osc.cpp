/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

#ifdef JUCE_EBEAMER_OSC_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

#include "ebeamer_osc.h"

#include "osc/ebeamer_ServerList.cpp"
#include "osc/ebeamer_OSCServerBroadcast.cpp"
#include "osc/ebeamer_OSCController.cpp"

namespace juce {

void     registerCommonOscParameters(OSCController& oscController){
    
    for (auto identifier : commonIdentifiersList){
        oscController.registerIdentifier(identifier);
    }
    
}

}
