/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/


/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.md file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:                 ebeamer_gui
  vendor:             Eventide
  version:            1.0.0
  name:               Ebeamer GUI classes
  description:      Ebeamer GUI libraries
  website:            http://www.eventideaudio.com
  license:            GPL/Commercial

  dependencies:       juce_gui_basics juce_audio_basics ebeamer_osc ebeamer_common

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#pragma once
#define JUCE_EBEAMER_GUI_H_INCLUDED

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <ebeamer_common/ebeamer_common.h>
#include <ebeamer_osc/ebeamer_osc.h>

#include "control/ebeamer_MidiPopup.h"
#include "control/ebeamer_MidiComp.h"
#include "control/ebeamer_ConfigComboBox.h"
#include "control/ebeamer_FrontToggle.h"
#include "control/ebeamer_FrequencySlider.h"
#include "control/ebeamer_DecibelSlider.h"
#include "control/ebeamer_HpfSlider.h"
#include "control/ebeamer_GainSlider.h"
#include "control/ebeamer_LevelSlider.h"
#include "control/ebeamer_LCRSlider.h"
#include "control/ebeamer_PanSlider.h"
#include "control/ebeamer_WidthSlider.h"
#include "control/ebeamer_SteerSlider.h"
#include "control/ebeamer_TextToggleButton.h"
#include "control/ebeamer_MuteToggle.h"

#include "display/ebeamer_CpuLoad.h"
#include "display/ebeamer_RoundLed.h"
#include "display/ebeamer_ActivityLed.h"
#include "display/ebeamer_SingleChannelLedBar.h"
#include "display/ebeamer_MultiChannelLedBar.h"
#include "display/ebeamer_Tile.h"
#include "display/ebeamer_TilesGrid.h"
#include "display/ebeamer_Beam.h"
#include "display/ebeamer_Scene.h"

#define SMALL_MARGIN 5
#define MEDIUM_MARGIN 10
#define LARGE_MARGIN 15

#define BOTTOM_MARGIN 16

#define HOR_SLIDER_HEIGHT 25
#define VER_SLIDER_WIDTH 70

#define LABEL_WIDTH 70
#define LABEL_HEIGHT 20

#define CENTRAL_LABEL_WIDTH 80
#define SMALL_LABEL_WIDTH 25

#define KNOB_SIZE 80
#define MUTE_SIZE 40

#define LED_SIZE 5

#define OSC_IP_LABEL_WIDTH 20
#define OSC_IP_WIDTH 150

#define OSC_PORT_LABEL_WIDTH 60
#define OSC_PORT_WIDTH 55

#define OSC_CONNECT_WIDTH 100
#define OSC_CONNECT_MARGIN_LEFT 15

#define CONTROLS_HEIGHT 30

#define MIN_HEIGHT 860
#define MIN_WIDTH 540

#define MAX_HEIGHT 1366
#define MAX_WIDTH 1366

#define GUI_WIDTH 540
#define GUI_HEIGHT 830

namespace juce{

typedef JUCE_API enum {
    SERVER,
    CLIENT
} GuiType;


class JUCE_API EbeamerGUI  :
public Component,
private ValueTree::Listener,
private Button::Listener,
private ComboBox::Listener
{
    
public:
    //==============================================================================
    EbeamerGUI();
    ~EbeamerGUI() override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    class Callback{
    public:
        virtual ~Callback() = default;
        virtual bool oscConnect(const String& serverIp, int serverPort) {return false;};
        virtual bool oscDisconnect(const String& serverIp, int serverPort) {return false;};
        virtual bool isConnected() const {return false;};
    };
    
    void initClient(const String& appManufacturer,
              const String& appName,
              const String& appVersion,
              ValueTree vtSession,
              ValueTree vtPersistent,
              Callback* cb
              );
    
    void initServer(const String& appManufacturer,
              const String& appName,
              const String& appVersion,
              ValueTree vt,
              Callback* cb
              );
    
    void oscDisconnect();
    
    void enableMidi(MidiCC::Callback* );
    
private:
    
    void commonInit();
    
    GuiType guiType;
    Callback* callback = nullptr;
    
    String appVersion;
    String appName;
    String appManufacturer;
    
    //==============================================================================
    Scene scene;
    
    //==============================================================================
    Label steerLabel;
    SteerSlider steerBeamX1Slider, steerBeamX2Slider;
    SteerSlider steerBeamY1Slider, steerBeamY2Slider;
    
    //==============================================================================
    Label widthLabel;
    WidthSlider widthBeam1Knob, widthBeam2Knob;
    
    //==============================================================================
    Label panLabel;
    PanSlider panBeam1Knob, panBeam2Knob;
    
    //==============================================================================
    Label levelLabel;
    LevelSlider levelBeam1Knob, levelBeam2Knob;
    
    //==============================================================================
    Label muteLabel;
    MuteButton muteBeam1Button, muteBeam2Button;
    
    //==============================================================================
    MultiChannelLedBar inputMeter;
    SingleChannelLedBar beam1Meter, beam2Meter;
    
    //==============================================================================
    HpfSlider hpfSlider;
    
    //==============================================================================
    GainSlider gainSlider;
    
    //==============================================================================
    /** CPU load component */
    CpuLoad cpuLoad;
    
    //==============================================================================
    /** Swap side toggle component */
    FrontToggle frontToggle;
    
    //==============================================================================
    /** Configuration selection combo */
    ConfigComboBox configComboBox;
    
    //==============================================================================
    /* Layout functions */
    void layoutConfigOsc(Rectangle<int>& );
    
    //==============================================================================
    const std::vector<Colour> beamColours = {Colours::orangered, Colours::royalblue};
    
#ifdef TARGET_OS_IOS
    const bool controlTextBoxEditable = false;
#else
    const bool controlTextBoxEditable = true;
#endif
    
    //==============================================================================
    /** OSC */
    
    std::map<int,Server> servers;
    
    Value serverIp;
    Value serverPort;
        
    ComboBox oscIp;
    Label oscIpLabel;
    
    TextEditor oscPort;
    Label oscPortLabel;
    
    TextButton oscConnectButton;
    
    void oscConnect();
    
    //==============================================================================
    /* Listeners and callbacks */
    
    void buttonClicked (Button*) override;
    void comboBoxChanged(ComboBox *) override;
    void showConnectionErrorMessage (const String&);
    
    //==============================================================================
    /* ValueTree */
    ValueTree valueTree;
    
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged,
                                           const Identifier& property) override;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EbeamerGUI)
};

}
