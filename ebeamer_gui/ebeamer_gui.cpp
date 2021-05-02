/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

#ifdef JUCE_EBEAMER_GUI_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

#include "ebeamer_gui.h"

#include "control/ebeamer_MidiPopup.cpp"
#include "control/ebeamer_ConfigComboBox.cpp"
#include "control/ebeamer_FrontToggle.cpp"
#include "control/ebeamer_HpfSlider.cpp"
#include "control/ebeamer_GainSlider.cpp"
#include "control/ebeamer_LevelSlider.cpp"
#include "control/ebeamer_PanSlider.cpp"
#include "control/ebeamer_WidthSlider.cpp"
#include "control/ebeamer_SteerSlider.cpp"
#include "control/ebeamer_MuteToggle.cpp"

#include "display/ebeamer_CpuLoad.cpp"
#include "display/ebeamer_RoundLed.cpp"
#include "display/ebeamer_ActivityLed.cpp"
#include "display/ebeamer_SingleChannelLedBar.cpp"
#include "display/ebeamer_MultiChannelLedBar.cpp"
#include "display/ebeamer_Tile.cpp"
#include "display/ebeamer_TilesGrid.cpp"
#include "display/ebeamer_Beam.cpp"
#include "display/ebeamer_Scene.cpp"

namespace juce {

EbeamerGUI::EbeamerGUI()
{
    
}

EbeamerGUI::~EbeamerGUI()
{
}

void EbeamerGUI::commonInit(){
    
    //==============================================================================
    scene.init(
               valueTree.getPropertyAsValue(frontIdentifier, nullptr),
               valueTree.getPropertyAsValue(configIdentifier, nullptr),
               valueTree.getPropertyAsValue(energyIdentifier, nullptr),
               valueTree.getPropertyAsValue(steerX1Identifier, nullptr),
               valueTree.getPropertyAsValue(steerY1Identifier, nullptr),
               valueTree.getPropertyAsValue(width1Identifier, nullptr),
               valueTree.getPropertyAsValue(mute1Identifier, nullptr),
               valueTree.getPropertyAsValue(steerX2Identifier, nullptr),
               valueTree.getPropertyAsValue(steerY2Identifier, nullptr),
               valueTree.getPropertyAsValue(width2Identifier, nullptr),
               valueTree.getPropertyAsValue(mute2Identifier, nullptr)
               );
    scene.setBeamColors(beamColours);
    addAndMakeVisible(scene);
    
    //==============================================================================
    steerLabel.setText("STEER", NotificationType::dontSendNotification);
    steerLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(steerLabel);
    
    steerBeamX1Slider.init(valueTree.getPropertyAsValue(steerX1Identifier, nullptr),beamColours[0],controlTextBoxEditable,false);
    steerBeamX2Slider.init(valueTree.getPropertyAsValue(steerX2Identifier, nullptr),beamColours[1],controlTextBoxEditable,false);
    addAndMakeVisible(steerBeamX1Slider);
    addAndMakeVisible(steerBeamX2Slider);
    
    steerBeamY1Slider.init(valueTree.getPropertyAsValue(steerY1Identifier, nullptr),beamColours[0],controlTextBoxEditable,true);
    steerBeamY2Slider.init(valueTree.getPropertyAsValue(steerY2Identifier, nullptr),beamColours[1],controlTextBoxEditable,true);
    steerBeamY1Slider.setLabelVisible(false);
    steerBeamY2Slider.setLabelVisible(false);
    addAndMakeVisible(steerBeamY1Slider);
    addAndMakeVisible(steerBeamY2Slider);
    
    //==============================================================================
    widthLabel.setText("WIDTH", NotificationType::dontSendNotification);
    widthLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(widthLabel);

    widthBeam1Knob.init(valueTree.getPropertyAsValue(width1Identifier, nullptr),beamColours[0],controlTextBoxEditable);
    widthBeam2Knob.init(valueTree.getPropertyAsValue(width2Identifier, nullptr),beamColours[1],controlTextBoxEditable);
    addAndMakeVisible(widthBeam1Knob);
    addAndMakeVisible(widthBeam2Knob);
    
    //==============================================================================
    panLabel.setText("PAN", NotificationType::dontSendNotification);
    panLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(panLabel);

    panBeam1Knob.init(valueTree.getPropertyAsValue(pan1Identifier, nullptr),beamColours[0],controlTextBoxEditable);
    panBeam2Knob.init(valueTree.getPropertyAsValue(pan2Identifier, nullptr),beamColours[1],controlTextBoxEditable);
    
    addAndMakeVisible(panBeam1Knob);
    addAndMakeVisible(panBeam2Knob);
    
    //==============================================================================
    levelLabel.setText("LEVEL", NotificationType::dontSendNotification);
    levelLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(levelLabel);
    
    levelBeam1Knob.init(valueTree.getPropertyAsValue(level1Identifier, nullptr),beamColours[0],controlTextBoxEditable);
    levelBeam2Knob.init(valueTree.getPropertyAsValue(level2Identifier, nullptr),beamColours[1],controlTextBoxEditable);
    
    addAndMakeVisible(levelBeam1Knob);
    addAndMakeVisible(levelBeam2Knob);
    
    //==============================================================================
    muteLabel.setText("MUTE", NotificationType::dontSendNotification);
    muteLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(muteLabel);
    
    muteBeam1Button.init(valueTree.getPropertyAsValue(mute1Identifier, nullptr),"1");
    muteBeam2Button.init(valueTree.getPropertyAsValue(mute2Identifier, nullptr),"2");
    
    addAndMakeVisible(muteBeam1Button);
    addAndMakeVisible(muteBeam2Button);
    
    //==============================================================================
    
    beam1Meter.init(valueTree.getPropertyAsValue(outMeter1Identifier, nullptr));
    beam2Meter.init(valueTree.getPropertyAsValue(outMeter2Identifier, nullptr));
    addAndMakeVisible(beam1Meter);
    addAndMakeVisible(beam2Meter);
    
    //==============================================================================
    
    hpfSlider.init(valueTree.getPropertyAsValue(hpfIdentifier, nullptr),controlTextBoxEditable);
    addAndMakeVisible(hpfSlider);
    
    //==============================================================================

    inputMeter.init(valueTree.getPropertyAsValue(inMetersIdentifier, nullptr));
    addAndMakeVisible(inputMeter);
    
    //==============================================================================
    // Gain
    gainSlider.init(valueTree.getPropertyAsValue(gainIdentifier, nullptr),controlTextBoxEditable);
    addAndMakeVisible(gainSlider);
    
    //=====================================================
    // Add CPU Load
    cpuLoad.init(valueTree.getPropertyAsValue(cpuIdentifier, nullptr));
    addAndMakeVisible(cpuLoad);
    
    //=====================================================
    // Add front facing toggle
    frontToggle.init(valueTree.getPropertyAsValue(frontIdentifier, nullptr));
    addAndMakeVisible(frontToggle);
    
    //=====================================================
    // Configuration selection combo
    configComboBox.init(valueTree.getPropertyAsValue(configIdentifier, nullptr));
    addAndMakeVisible(configComboBox);
    
    /* Initialize OSC */
    oscIpLabel.setText("IP", NotificationType::dontSendNotification);
    oscIpLabel.attachToComponent(&oscIp, true);
    oscIp.setJustificationType(Justification::centred);
    oscIp.setEditableText(true);
    oscIp.setText(serverIp.toString(),dontSendNotification);
    oscIp.addListener(this);
    addAndMakeVisible(oscIp);
    
    oscPortLabel.setText("PORT", NotificationType::dontSendNotification);
    oscPortLabel.attachToComponent(&oscPort, true);
    oscPort.setText(serverPort.toString(),dontSendNotification);
    oscPort.setJustification(Justification::centred);
    oscPort.setKeyboardType(TextInputTarget::numericKeyboard);
    oscPort.onReturnKey = [this]{oscConnect();};
    addAndMakeVisible(oscPort);
    
    oscConnectButton.setButtonText("Connect");
    oscConnectButton.addListener(this);
    addAndMakeVisible(oscConnectButton);
    
    //=====================================================
    valueTree.addListener(this);
    
}

void EbeamerGUI::initClient(const String& appManufacturer_,
                 const String& appName_,
                 const String& appVersion_,
                 ValueTree vtSession,
                 ValueTree vtPersistent,
                 Callback* cb_){
    
    appManufacturer = appManufacturer_;
    appName = appName_;
    appVersion = appVersion_;
    valueTree = vtSession;
    guiType = CLIENT;
    callback = cb_;

    serverIp = vtPersistent.getPropertyAsValue(serverIpIdentifier, nullptr);
    serverPort = vtPersistent.getPropertyAsValue(serverPortIdentifier, nullptr);
    
    oscIp.setText(serverIp.toString());
    oscPort.setText(serverPort.toString());
    
    commonInit();
}


void EbeamerGUI::initServer(const String& appManufacturer_,
                 const String& appName_,
                 const String& appVersion_,
                 ValueTree vt,
                 Callback* cb_){
    
    appManufacturer = appManufacturer_;
    appName = appName_;
    appVersion = appVersion_;
    valueTree = vt;
    guiType = SERVER;
    callback = cb_;

    serverPort = valueTree.getPropertyAsValue(serverPortIdentifier, nullptr);
    oscPort.setText(serverPort.toString());
    oscPort.setEnabled(false);
    
    commonInit();
    
}

void EbeamerGUI::enableMidi(MidiCC::Callback* cb){
    steerBeamX1Slider.enableMidi(cb,steerX1Identifier);
    steerBeamX2Slider.enableMidi(cb,steerX2Identifier);
    steerBeamY1Slider.enableMidi(cb,steerY1Identifier);
    steerBeamY2Slider.enableMidi(cb,steerY2Identifier);
    widthBeam1Knob.enableMidi(cb,width1Identifier);
    widthBeam2Knob.enableMidi(cb,width2Identifier);
    panBeam1Knob.enableMidi(cb,pan1Identifier);
    panBeam2Knob.enableMidi(cb,pan2Identifier);
    levelBeam1Knob.enableMidi(cb,level1Identifier);
    levelBeam2Knob.enableMidi(cb,level2Identifier);
    muteBeam1Button.enableMidi(cb, mute1Identifier);
    muteBeam2Button.enableMidi(cb, mute2Identifier);
    gainSlider.enableMidi(cb,gainIdentifier);
    hpfSlider.enableMidi(cb,hpfIdentifier);
    frontToggle.enableMidi(cb, frontIdentifier);
}

//==============================================================================
void EbeamerGUI::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    
    g.setColour(Colours::white);
    g.setFont(15.0f);
    
    auto versionArea = getBounds().removeFromBottom(12);
    versionArea.removeFromBottom(2);
    g.setColour(Colours::lightgrey);
    g.setFont(12);
    g.drawText(appManufacturer + " - " + appName + " " + appVersion, versionArea, Justification::centredBottom, false);
}

void EbeamerGUI::resized()
{
    
    if (!valueTree.isValid()){
        return;
    }
    
    auto area = getLocalBounds();
    const bool portrait = area.getHeight() > area.getWidth();
    
    /* Overall minimum margin */
    const int screenMargin = jmin(5,(int)(0.03*area.getWidth()));
    area.removeFromLeft(screenMargin+SMALL_MARGIN);
    area.removeFromRight(screenMargin+SMALL_MARGIN);
    area.removeFromTop(screenMargin);
    area.removeFromBottom(screenMargin);
    
    /* Controls area */
    layoutConfigOsc(area);
    
    if (portrait){
        
        /* Landscape-only labels */
        steerBeamX1Slider.setLabelText("1");
        steerBeamX2Slider.setLabelText("2");
        widthBeam1Knob.setLabelVisible(false);
        widthBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        panBeam1Knob.setLabelVisible(false);
        panBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        levelBeam1Knob.setLabelVisible(false);
        levelBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam1Button.setLabelVisible(false);
        muteBeam1Button.setFakeTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam1Button.setFakeTextBoxLineVisible(true);
        
        widthBeam2Knob.setLabelVisible(false);
        widthBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        panBeam2Knob.setLabelVisible(false);
        panBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        levelBeam2Knob.setLabelVisible(false);
        levelBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        muteBeam2Button.setLabelVisible(false);
        muteBeam2Button.setFakeTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxLeft);
        muteBeam2Button.setFakeTextBoxLineVisible(true);
        
        /* Portrait-only labels */
        steerLabel.setVisible(true);
        widthLabel.setVisible(true);
        panLabel.setVisible(true);
        muteLabel.setVisible(true);
        levelLabel.setVisible(true);
        
        /* Scene, aspect ratio 2:1 */
        auto sceneArea = area.removeFromTop(jmin(area.getWidth()/2,area.getHeight()/3));
        sceneArea = sceneArea.withSizeKeepingCentre(sceneArea.getHeight()*2, sceneArea.getHeight());
        
        if (isLinearArray(valueTree[configIdentifier])){
            steerBeamY1Slider.setVisible(false);
            steerBeamY2Slider.setVisible(false);
            scene.setBounds(sceneArea);
        }else{
            steerBeamY1Slider.setVisible(true);
            steerBeamY2Slider.setVisible(true);
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            steerBeamY1Slider.setBounds(sceneArea.removeFromLeft(VER_SLIDER_WIDTH));
            steerBeamY2Slider.setBounds(sceneArea.removeFromRight(VER_SLIDER_WIDTH));
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            scene.setBounds(sceneArea);
        }
        
        /* Gain slider */
        area.removeFromBottom(LARGE_MARGIN);
        gainSlider.setBounds(area.removeFromBottom(HOR_SLIDER_HEIGHT));
        
        /* Input LED */
        area.removeFromBottom(MEDIUM_MARGIN);
        inputMeter.setBounds(area.removeFromBottom(LED_SIZE).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(LABEL_WIDTH));
        area.removeFromBottom(MEDIUM_MARGIN);
        
        /* HPF slider */
        hpfSlider.setBounds(area.removeFromBottom(HOR_SLIDER_HEIGHT));
        area.removeFromBottom(LARGE_MARGIN);
        
        /* Derive margins and sizes based on remaninig space */
        const int availableHeight = area.getHeight();
        const int usedHeight = MEDIUM_MARGIN+HOR_SLIDER_HEIGHT+SMALL_MARGIN+LABEL_HEIGHT+SMALL_MARGIN+HOR_SLIDER_HEIGHT+
        3*(MEDIUM_MARGIN+KNOB_SIZE)+LARGE_MARGIN+MUTE_SIZE;
        const int residualHeight = jmax(availableHeight - usedHeight,0);
        
        const int smallMargin = SMALL_MARGIN;
        const int mediumMargin = MEDIUM_MARGIN;
        const int largeMargin = LARGE_MARGIN;
        
        const int knobMuteTotalIncrease = residualHeight/4*3;
        const int horSliderTotalIncrease = residualHeight - knobMuteTotalIncrease;
        
        const int knobSize = KNOB_SIZE + knobMuteTotalIncrease/4;
        const int muteSize = MUTE_SIZE + knobMuteTotalIncrease/4;
        const int horSliderHeight = HOR_SLIDER_HEIGHT + horSliderTotalIncrease/2;
        
        const int controlsSideMargin = area.getWidth()*0.05;
        const int ledMeterWidth = area.getWidth()*0.05;
        
        /* Allocate elements from top to bottom */
        
        /* Horizontal steering */
        steerLabel.setVisible(true);
        
        area.removeFromTop(mediumMargin);
        steerBeamX1Slider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(SMALL_LABEL_WIDTH));
        area.removeFromTop(smallMargin);
        steerLabel.setBounds(area.removeFromTop(LABEL_HEIGHT));
        area.removeFromTop(smallMargin);
        steerBeamX2Slider.setBounds(area.removeFromTop(horSliderHeight).withTrimmedLeft(SMALL_LABEL_WIDTH));
        
        /* Width knobs */
        area.removeFromTop(mediumMargin);
        auto widthKnobsArea = area.removeFromTop(knobSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        widthLabel.setBounds(widthKnobsArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto width1Area = widthKnobsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        auto width2Area = widthKnobsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        width1Area.removeFromRight(ledMeterWidth);
        width2Area.removeFromLeft(ledMeterWidth);
        widthBeam1Knob.setBounds(width1Area);
        widthBeam2Knob.setBounds(width2Area);
        
        /* Pan knobs */
        area.removeFromTop(mediumMargin);
        auto panKnobsArea = area.removeFromTop(knobSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        panLabel.setBounds(panKnobsArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto pan1Area = panKnobsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        auto pan2Area = panKnobsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        pan1Area.removeFromRight(ledMeterWidth);
        pan2Area.removeFromLeft(ledMeterWidth);
        panBeam1Knob.setBounds(pan1Area);
        panBeam2Knob.setBounds(pan2Area);
        
        /* Levels and meters */
        area.removeFromTop(mediumMargin);
        auto levelsArea = area.removeFromTop(knobSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        levelLabel.setBounds(levelsArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto level1Area = levelsArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        auto level2Area = levelsArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        beam1Meter.setBounds(level1Area.removeFromRight(ledMeterWidth).withSizeKeepingCentre(LED_SIZE, level1Area.getHeight()));
        beam2Meter.setBounds(level2Area.removeFromLeft(ledMeterWidth).withSizeKeepingCentre(LED_SIZE, level2Area.getHeight()));
        levelBeam1Knob.setBounds(level1Area);
        levelBeam2Knob.setBounds(level2Area);
        
        
        /* Mutes */
        area.removeFromTop(largeMargin);
        auto mutesArea = area.removeFromTop(muteSize).withTrimmedLeft(controlsSideMargin).withTrimmedRight(controlsSideMargin);
        muteLabel.setBounds(mutesArea.withSizeKeepingCentre(CENTRAL_LABEL_WIDTH, LABEL_HEIGHT));
        auto mute1Area = mutesArea.removeFromLeft((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        auto mute2Area = mutesArea.removeFromRight((area.getWidth()-CENTRAL_LABEL_WIDTH)/2-controlsSideMargin);
        muteBeam1Button.setBounds(mute1Area);
        muteBeam2Button.setBounds(mute2Area);
        

    }else{
        
        /* Landscape-only labels */
        steerBeamX1Slider.setLabelText("STEER 1");
        steerBeamX2Slider.setLabelText("STEER 2");
        widthBeam1Knob.setLabelVisible(true);
        widthBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        panBeam1Knob.setLabelVisible(true);
        panBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        levelBeam1Knob.setLabelVisible(true);
        levelBeam1Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam1Button.setLabelVisible(true);
        muteBeam1Button.setFakeTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam1Button.setFakeTextBoxLineVisible(false);
        
        widthBeam2Knob.setLabelVisible(true);
        widthBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        panBeam2Knob.setLabelVisible(true);
        panBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        levelBeam2Knob.setLabelVisible(true);
        levelBeam2Knob.setTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam2Button.setLabelVisible(true);
        muteBeam2Button.setFakeTextBoxPosition(Slider::TextEntryBoxPosition::TextBoxRight);
        muteBeam2Button.setFakeTextBoxLineVisible(false);
        
        /* Portrait-only labels */
        steerLabel.setVisible(false);
        widthLabel.setVisible(false);
        panLabel.setVisible(false);
        muteLabel.setVisible(false);
        levelLabel.setVisible(false);
        
        auto sceneArea = area.removeFromTop(area.getHeight()/2);
        
        if (isLinearArray(valueTree[configIdentifier])){
            steerBeamY1Slider.setVisible(false);
            steerBeamY2Slider.setVisible(false);
        }else{
            steerBeamY1Slider.setVisible(true);
            steerBeamY2Slider.setVisible(true);
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
            steerBeamY1Slider.setBounds(sceneArea.removeFromLeft(VER_SLIDER_WIDTH));
            steerBeamY2Slider.setBounds(sceneArea.removeFromRight(VER_SLIDER_WIDTH));
            sceneArea.removeFromLeft(SMALL_MARGIN);
            sceneArea.removeFromRight(SMALL_MARGIN);
        }
        
        /* Scene, aspect ratio 2:1 */
        scene.setBounds(sceneArea);
        
        /* Input section */
        
        /* Input LED */
        area.removeFromBottom(BOTTOM_MARGIN);
        inputMeter.setBounds(area.removeFromBottom(LED_SIZE).withTrimmedLeft(LABEL_WIDTH).withTrimmedRight(LABEL_WIDTH));
        area.removeFromBottom(MEDIUM_MARGIN);
        
        /* HPF slider */
        auto inputSlidersArea = area.removeFromBottom(HOR_SLIDER_HEIGHT);
        hpfSlider.setBounds(inputSlidersArea.removeFromLeft(inputSlidersArea.getWidth()/2).withTrimmedRight(MEDIUM_MARGIN));
        
        /* Gain slider */
        gainSlider.setBounds(inputSlidersArea.withTrimmedRight(MEDIUM_MARGIN));
        
        area.removeFromBottom(LARGE_MARGIN);
        
        /* Dynamic geometry section */
        const int availableHeight = area.getHeight();
        const int usedHeight = SMALL_MARGIN+HOR_SLIDER_HEIGHT+SMALL_MARGIN+KNOB_SIZE+SMALL_MARGIN+KNOB_SIZE;
        const int residualHeight = jmax(availableHeight - usedHeight,0);
        
        const int knobMuteTotalIncrease = residualHeight/3;
        const int horSliderTotalIncrease = residualHeight/3;
        const int marginIncrease = residualHeight - knobMuteTotalIncrease - horSliderTotalIncrease;
        
        const int smallMargin = SMALL_MARGIN + marginIncrease/3;
        
        const int knobSize = KNOB_SIZE + knobMuteTotalIncrease/2;
        const int muteSize = MUTE_SIZE + knobMuteTotalIncrease/2;
        const int horSliderHeight = HOR_SLIDER_HEIGHT + horSliderTotalIncrease;
        
        const int ledMeterWidth = area.getWidth()*0.05;
        
        /* Beams section */
        
        auto beam1Area = area.removeFromLeft(area.getWidth()/2).withTrimmedRight(MEDIUM_MARGIN);
        auto beam2Area = area.withTrimmedLeft(MEDIUM_MARGIN);
        
        /* Beam 1 */
        
        beam1Area.removeFromTop(smallMargin);
        steerBeamX1Slider.setBounds(beam1Area.removeFromTop(horSliderHeight));
        
        beam1Area.removeFromTop(smallMargin);
        auto widthPanArea1 = beam1Area.removeFromTop(knobSize);
        widthBeam1Knob.setBounds(widthPanArea1.removeFromLeft(beam1Area.getWidth()/2));
        panBeam1Knob.setBounds(widthPanArea1);
        
        beam1Area.removeFromTop(smallMargin);
        auto levelMuteArea1 = beam1Area.removeFromTop(knobSize);
        levelBeam1Knob.setBounds(levelMuteArea1.removeFromRight(levelMuteArea1.getWidth()/2));
        muteBeam1Button.setBounds(levelMuteArea1.withSizeKeepingCentre(levelMuteArea1.getWidth(), muteSize));
        beam1Meter.setBounds(levelMuteArea1.removeFromRight(ledMeterWidth).withSizeKeepingCentre(LED_SIZE, levelMuteArea1.getHeight()));
        
        
        /* Beam 2 */
        
        beam2Area.removeFromTop(smallMargin);
        steerBeamX2Slider.setBounds(beam2Area.removeFromTop(horSliderHeight));
        
        beam2Area.removeFromTop(smallMargin);
        auto widthPanArea2 = beam2Area.removeFromTop(knobSize);
        widthBeam2Knob.setBounds(widthPanArea2.removeFromLeft(beam2Area.getWidth()/2));
        panBeam2Knob.setBounds(widthPanArea2);
        
        beam2Area.removeFromTop(smallMargin);
        auto levelMuteArea2 = beam2Area.removeFromTop(knobSize);
        levelBeam2Knob.setBounds(levelMuteArea2.removeFromRight(levelMuteArea2.getWidth()/2));
        muteBeam2Button.setBounds(levelMuteArea2.withSizeKeepingCentre(levelMuteArea2.getWidth(), muteSize));
        beam2Meter.setBounds(levelMuteArea2.removeFromRight(ledMeterWidth).withSizeKeepingCentre(LED_SIZE, levelMuteArea2.getHeight()));
        
    }


}

void EbeamerGUI::layoutConfigOsc(Rectangle<int>& area){
    
    Rectangle<int> oscArea,setupArea;
    
    const int oscWidth = guiType==CLIENT ? OSC_IP_LABEL_WIDTH+OSC_IP_WIDTH+OSC_PORT_LABEL_WIDTH+OSC_PORT_WIDTH+OSC_CONNECT_MARGIN_LEFT+OSC_CONNECT_WIDTH : OSC_PORT_LABEL_WIDTH+OSC_PORT_WIDTH;
    
    const int configWidth = cpuLoad.getMinWidth()+SMALL_MARGIN+configComboBox.getMinWidth()+SMALL_MARGIN+frontToggle.getMinWidth();
    auto remainingWidth = area.getWidth() - (oscWidth+configWidth+SMALL_MARGIN);
    if (remainingWidth >= 0){
        auto oscControlArea = area.removeFromTop(CONTROLS_HEIGHT);
        oscControlArea.removeFromLeft(remainingWidth/2);
        oscArea = oscControlArea.removeFromLeft(oscWidth);
        oscControlArea.removeFromLeft(SMALL_MARGIN);
        setupArea = oscControlArea.removeFromLeft(configWidth);
    }else{
        setupArea = area.removeFromTop(CONTROLS_HEIGHT).withSizeKeepingCentre(configWidth, CONTROLS_HEIGHT);
        area.removeFromTop(MEDIUM_MARGIN);
        oscArea = area.removeFromTop(CONTROLS_HEIGHT).withSizeKeepingCentre(oscWidth, CONTROLS_HEIGHT);
    }
    area.removeFromTop(SMALL_MARGIN);
    
    
    /* OSC controls */
    if (guiType == CLIENT){
        oscArea.removeFromLeft(OSC_IP_LABEL_WIDTH);
        oscIp.setBounds(oscArea.removeFromLeft(OSC_IP_WIDTH));
    }
    oscArea.removeFromLeft(OSC_PORT_LABEL_WIDTH);
    oscPort.setBounds(oscArea.removeFromLeft(OSC_PORT_WIDTH));
    
    if (guiType == CLIENT){
        oscArea.removeFromLeft(OSC_CONNECT_MARGIN_LEFT);
        oscConnectButton.setBounds(oscArea.removeFromLeft(OSC_CONNECT_WIDTH));
    }
    
    /* Set area for CPU Load */
    cpuLoad.setBounds(setupArea.removeFromLeft(cpuLoad.getMinWidth()));
    
    /* Set area for config combo */
    setupArea.removeFromLeft(SMALL_MARGIN);
    configComboBox.setBounds(setupArea.removeFromLeft(configComboBox.getMinWidth()));

    /* Set area for front toggle */
    setupArea.removeFromLeft(SMALL_MARGIN);
    frontToggle.setBounds(setupArea.removeFromLeft(frontToggle.getMinWidth()));
}

//====================================================================
/* OSC operations */
void EbeamerGUI::oscConnect(){
    serverIp.setValue(oscIp.getText());
    serverPort.setValue(jmin(oscPort.getTextValue().toString().getIntValue(),65535));
    if (callback != nullptr){
        if (!callback->isConnected()){
            if(callback->oscConnect(serverIp.toString(),serverPort.getValue())){
                oscConnectButton.setButtonText("Disconnect");
                oscIp.setEnabled(false);
                oscPort.setEnabled(false);
            }
        }
    }
}

void EbeamerGUI::oscDisconnect(){
    if (callback != nullptr){
        if (callback->isConnected()){
            if (callback->oscDisconnect(serverIp.toString(),serverPort.getValue())){
                oscConnectButton.setButtonText("Connect");
                oscIp.setEnabled(true);
                oscPort.setEnabled(true);
                /* Reset graphic components */
                inputMeter.reset();
                beam1Meter.reset();
                beam2Meter.reset();
                scene.reset();
            }
        }
    }
}
//====================================================================
/* Callbacks and listeners */

void EbeamerGUI::buttonClicked (Button* button){
    if (button == &oscConnectButton){
        if (callback != nullptr){
            if (callback->isConnected()){
                oscDisconnect();
            }else{
                oscConnect();
            }
        }
    }
}

void EbeamerGUI::comboBoxChanged(ComboBox * comboBox){
    if (comboBox == &oscIp){
        auto selectedId = oscIp.getSelectedId();
        if (selectedId > 0){
            auto selectedServer = servers[selectedId];
            oscIp.setText(selectedServer.ip,dontSendNotification);
            oscPort.setText(String(selectedServer.port),dontSendNotification);
        }
    }
}

void EbeamerGUI::valueTreePropertyChanged (ValueTree& vt,
                               const Identifier& property){
    if (property == serversIdentifier){
        oscIp.clear();
        servers.clear();
        const Time now = Time::getCurrentTime();
        for (auto srvArr : *vt.getProperty(property).getArray()){
            String ip = srvArr[0].toString();
            int32 port = int(srvArr[1]);
            int32 id = int(srvArr[2]);
            servers[id] = Server({ip,port,now});
            oscIp.addItem(servers[id].toString(), id);
        }
        if (oscIp.isPopupActive()){
            oscIp.hidePopup();
        }
    }else if (property == configIdentifier){
        resized();
    }else if (property == serverPortIdentifier){
        oscPort.setText(vt[serverPortIdentifier].toString());
    }
}


}
