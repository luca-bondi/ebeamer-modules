/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API SliderCC : public Slider{
public:
    SliderCC(){};
    
    ~SliderCC() override {};
    
    void enableMidi(MidiCC::Callback* cb, const String& param){
        midiPopup = std::make_unique<MidiPopup>(*this,cb,param);
    }

    void mouseDown(const MouseEvent &e) override {
        if (midiPopup != nullptr && e.mods.isPopupMenu()) {
            midiPopup->showPopupMenu();
        } else {
            Slider::mouseDown(e);
        }
    }

private:
    std::unique_ptr<MidiPopup> midiPopup = nullptr;

};

//==============================================================================
class JUCE_API TextButtonCC : public TextButton{
public:
    TextButtonCC() {};

    ~TextButtonCC() override {};
    
    void enableMidi(MidiCC::Callback* cb, const String& param){
        midiPopup = std::make_unique<MidiPopup>(*this,cb,param);
    }

    void mouseDown(const MouseEvent &e) override {

        if (midiPopup != nullptr && e.mods.isPopupMenu()) {
            midiPopup->showPopupMenu();
        } else {
            TextButton::mouseDown(e);
        }
    }

    void mouseUp(const MouseEvent &e) override {
        if (!e.mods.isPopupMenu()){
            TextButton::mouseUp(e);
        }
    }

private:
    std::unique_ptr<MidiPopup> midiPopup = nullptr;

};


//==============================================================================
class JUCE_API ToggleButtonCC : public ToggleButton {
public:
    ToggleButtonCC(){};

    ~ToggleButtonCC() override {};
    
    void enableMidi(MidiCC::Callback* cb, const String& param){
        midiPopup = std::make_unique<MidiPopup>(*this,cb,param);
    }

    void mouseDown(const MouseEvent &e) override {
        if (midiPopup != nullptr && e.mods.isPopupMenu()) {
            midiPopup->showPopupMenu();
        } else {
            ToggleButton::mouseDown(e);
        }
    }

    void mouseUp(const MouseEvent &e) override {
        if (!e.mods.isPopupMenu()){
            ToggleButton::mouseUp(e);
        }
    }
    
private:
    std::unique_ptr<MidiPopup> midiPopup = nullptr;
};

}
