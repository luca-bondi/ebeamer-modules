/*
  ==============================================================================

 Ebeamer common module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

bool isLinearArray(MicConfig m){
    switch(m){
        case ULA_1ESTICK:
        case ULA_2ESTICK:
        case ULA_3ESTICK:
        case ULA_4ESTICK:
            return true;
        case URA_2ESTICK:
        case URA_3ESTICK:
        case URA_4ESTICK:
        case URA_2x2ESTICK:
            return false;
        default:
            jassertfalse;
            return true;
    }
};

bool isLinearArray(int m){
    return isLinearArray(static_cast<MicConfig>(m));
}

bool isLinearArray(var m){
    jassert(m.isInt());
    return isLinearArray(int(m));
}
} /* end namespace juce */
