/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

//==============================================================================
namespace juce{

OSCServerBroadcast::OSCServerBroadcast(const String& address_, int port_){
    address = address_;
    receiverPort = port_;
    
    startTimerHz(timerFreq);
    
}

OSCServerBroadcast::~OSCServerBroadcast(){
    
}

void OSCServerBroadcast::timerCallback(){

    auto ipArray = IPAddress::getAllAddresses(false);
    ipArray.remove(0);

    for (auto ip : ipArray){
        OSCSender sender;
        sender.connectToSocket(socket,IPAddress::getInterfaceBroadcastAddress(ip).toString(), BROADCAST_PORT);
        OSCMessage msg(address);
        msg.addString(ip.toString());
        msg.addInt32(receiverPort);
        sender.send(msg);
    }

}

}  /* end namespace juce */
