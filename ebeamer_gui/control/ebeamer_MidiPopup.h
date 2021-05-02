/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API MidiPopup {
public:
    MidiPopup(Component &owner, MidiCC::Callback *cb, const String &param);

    ~MidiPopup(){};

    void showPopupMenu();

private:
    MidiCC::Callback *callback = nullptr;
    String paramName = "";
    Rectangle<int> popupArea;
    Component &owner;

    static void sliderMenuCallback(int result, MidiPopup *popup);

    bool isLearning() const;
};

} /* end namespace juce */
