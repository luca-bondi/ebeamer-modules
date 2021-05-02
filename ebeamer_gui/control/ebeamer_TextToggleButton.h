/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API TextToggleButton  : public TextButtonCC
{
public:
    TextToggleButton(){
        setClickingTogglesState(true);
    };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextToggleButton)
};

} /* end namespace juce */
