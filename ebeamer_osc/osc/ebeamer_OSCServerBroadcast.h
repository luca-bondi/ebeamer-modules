/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/


namespace juce{

class JUCE_API OSCServerBroadcast:
private Timer
{
  
public:
    OSCServerBroadcast(const String& address, int port);
    ~OSCServerBroadcast();
    
private:
    
    /** UDP socket */
    DatagramSocket socket = DatagramSocket(true);
    
    /** Announce address */
    String address;
    
    /** Receiver port */
    int receiverPort;
    
    /** Timer callback */
    void timerCallback() override;
    
    /** Announce frequency [Hz] */
    const float timerFreq = 5;
    
    
};

}; /* end namespace juce */
