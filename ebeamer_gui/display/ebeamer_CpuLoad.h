/*
  ==============================================================================

   Ebeamer GUI module
   Eventide Inc.
   Copyright Eventide Inc. 2021
   Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

class JUCE_API CpuLoad:
public Component,
private Value::Listener
{
    
public:
    
    CpuLoad();
    ~CpuLoad();
    
    void init(Value);
    void paint(Graphics &) override;
    
    void resized() override;
    
    int getMinWidth() const;
    
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CpuLoad)
    
    Value value;
    
    const String labelText = "CPU";
    
    const int labelWidth = 40;
    const int contentWidth = 45;
    
    Label label;
    Label content;
    
    void valueChanged (Value&) override;
    
};

} /* end namespace juce */
