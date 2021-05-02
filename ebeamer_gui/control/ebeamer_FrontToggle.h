/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API FrontToggle:
public Component,
private Button::Listener,
private Value::Listener
{
    
public:
    
    FrontToggle();
    ~FrontToggle();
    
    void init(Value);
    void paint(Graphics &) override;
    
    void resized() override;
    
    int getMinWidth() const;
    
    void enableMidi(MidiCC::Callback*, const Identifier& identifier);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrontToggle)
    
    Value value;
    
    const String labelText = "FRONT";
    
    const int labelWidth = 60;
    const int contentWidth = 25;
    
    Label label;
    ToggleButtonCC button;
    
    void buttonClicked (Button*) override {};
    void buttonStateChanged(Button *) override;
    void valueChanged (Value&) override;
    
};

} /* end namespace juce */
