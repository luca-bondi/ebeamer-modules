/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API ConfigComboBox:
public Component,
private ComboBox::Listener,
private Value::Listener
{
    
public:
    
    ConfigComboBox();
    ~ConfigComboBox();
    
    void init(Value);
    void paint(Graphics &) override;
    
    void resized() override;
    
    int getMinWidth() const;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConfigComboBox)
    
    Value value;
    
    const String labelText = "SETUP";
    
    const int labelWidth = 55;
    const int contentWidth = 105;
    
    Label label;
    ComboBox combo;
    
    void comboBoxChanged(ComboBox *) override;
    void valueChanged (Value&) override;
    
};

} /* end namespace juce */
