/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API MuteButton:
public Component,
private Button::Listener,
private Value::Listener
{
    
public:
    
    MuteButton();
    ~MuteButton();
    
    void init(Value, const String& );
    void setFakeTextBoxPosition(Slider::TextEntryBoxPosition pos);
    void setFakeTextBoxLineVisible(bool v);
    
    void setLabelVisible(bool);
    
    void paint(Graphics &) override;
    
    void resized() override;
    
    int getMinWidth() const;
    
    void enableMidi(MidiCC::Callback*, const Identifier& identifier);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MuteButton)
    
    Value value;
    
    const String labelText = "MUTE";
    
    const int labelWidth = 60;
    const int margin = 5;
    const int contentWidth = 60;
    
    const int textBoxWidth = 70;
    Slider::TextEntryBoxPosition textBoxPos;
    Rectangle<int> fakeTextBoxArea;
    bool fakeTextBoxLineVisible = false;
    const float fakeTextBoxLineThickness = 1;
    const int fakeTextBoxLineMargin = 25;
    
    Label label;
    TextToggleButton button;
    
    void buttonClicked (Button*) override {};
    void buttonStateChanged(Button *) override;
    void valueChanged (Value&) override;
    
};

} /* end namespace juce */
