/*
  ==============================================================================

 Ebeamer common module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

/** Available eSticks configurations type */
typedef JUCE_API enum {
    ULA_1ESTICK,
    ULA_2ESTICK,
    ULA_3ESTICK,
    ULA_4ESTICK,
    URA_2ESTICK,
    URA_3ESTICK,
    URA_4ESTICK,
    URA_2x2ESTICK,
} MicConfig;

/** Available eSticks configurations labels */
const StringArray micConfigLabels({
                                          "Single",
                                          "Horiz 2",
                                          "Horiz 3",
                                          "Horiz 4",
                                          "Stack 2",
                                          "Stack 3",
                                          "Stack 4",
                                          "Stack 2x2",
                                  });

bool isLinearArray(MicConfig m);
bool isLinearArray(int m);
bool isLinearArray(var m);

} /* end namespace juce */
