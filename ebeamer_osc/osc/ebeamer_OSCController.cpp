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

OSCController::OSCController(){
    
}

OSCController::~OSCController(){
    
}

void OSCController::init(ValueTree vt){
    jassert(vt.isValid());
    valueTree = vt;
    valueTree.addListener(this);
    serverList.setValueTree(vt);
}

/** Start listening for broadcast messages from the Ebeamer on the same LAN */
void OSCController::initBroadcastReceiver(const Identifier& ident){
    
    /* Non-exclusive listener on broadcast port */
    if (!broadcastSocket.setEnablePortReuse(true)){
        std::cerr << "Error while trying to setup broadcast receiver. Unable to set port for reuse" << std::endl;
        return;
    }
    
    /* Bind to port */
    if (!broadcastSocket.bindToPort(BROADCAST_PORT)){
        std::cerr << "Error while trying to setup broadcast receiver. Unable to bind to port " + String(BROADCAST_PORT) << std::endl;
        return;
    }
    
    /* Connect receiver to socket */
    if (!broadcastReceiver.connectToSocket(broadcastSocket)){
        std::cerr << "Error while trying to setup broadcast receiver. Unable to connect to socket" << std::endl;
        return;
    }
    
    /* Set broadcast announce identifier */
    serverList.setIdentifier(ident);
    
    /* Register announceAddress */
    registerIdentifier(announceIdentifier);
    
    /* Set listener on announce address */
    broadcastReceiver.addListener(this, announceAddress);
}

void OSCController::sendDump(const Server& srv){
    
    for (auto identifier : commonIdentifiersList){
        send(identifier,valueTree[identifier]);
    }
    
}

Time OSCController::lastMessageReceivedAt() const{
    return lastReceivedMessageTime;
}

void OSCController::oscMessageReceived (const OSCMessage& message){
  
    /** Parameters and status messages */
    const String oscAddress = message.getAddressPattern().toString();
    
    if (!registeredIdentifiersMap.contains(oscAddress)){
        return;
    }
    
    /** Announce messages */
    if (oscAddress == announceAddress){
        if ((message.size()==2) && (message[0].isString()) && (message[1].isInt32())){
            Server server({message[0].getString(),message[1].getInt32()});
            serverList.addOrUpdate(server);
        }
        return;
    }
    
    /** Get message */
    if (oscAddress == getAddress){
        if ((message.size()==2) && (message[0].isString()) && (message[1].isInt32())){
            const Server srv({message[0].getString(),message[1].getInt32()});
            sendDump(srv);
        }
        return;
    }
    
    /** Subscribe message */
    if (oscAddress == oscPrefix+subscribeIdentifier){
        if (message.size()==2 && (message[0].isString() && message[1].isInt32())){
            const Server srv({message[0].getString(),message[1].getInt32()});
            addSender(srv);
            sendDump(srv);
        }else{
            jassertfalse;
        }
        return;
    }
    
    /** Unubscribe message */
    if (oscAddress == oscPrefix+unsubscribeIdentifier){
        if (message.size()==2 && (message[0].isString() && message[1].isInt32())){
            const Server srv({message[0].getString(),message[1].getInt32()});
            removeSender(srv);
        }else{
            jassertfalse;
        }
        return;
    }
    
    const Identifier id = registeredIdentifiersMap[oscAddress];
    var val;
        
    switch(message.size()){
        case 1:{
            if(message[0].isInt32()){
                val = message[0].getInt32();
            }else if (message[0].isFloat32()){
                val = message[0].getFloat32();
            }else if (message[0].isBlob()){
                val = message[0].getBlob();
            }else {
                jassertfalse;
            }
            break;
        }
        default:{
            jassertfalse;
        }
    }
    
    valueTree.setPropertyExcludingListener(this, id, val, nullptr);
    lastReceivedMessageTime = Time::getCurrentTime();
    
}

void OSCController::registerIdentifier(const Identifier& id){
    if (registeredIdentifiersMap.containsValue(id)){
        std::cerr << "Error: identifier already registered " << id.toString() << std::endl;
        jassertfalse;
        return;
    }
    const String addressPattern = oscPrefix+id;
    registeredIdentifiersMap.set(addressPattern, id);
    
    if (receiverEnabled)
        receiver.addListener(this,addressPattern);
}

void OSCController::unregisterIdentifier(const Identifier& id){
    if (!registeredIdentifiersMap.containsValue(id)){
        std::cerr << "Error: identifier not registered " << id.toString() << std::endl;
        jassertfalse;
        return;
    }
    const String addressPattern = oscPrefix+id;
    registeredIdentifiersMap.remove(addressPattern);
}

void OSCController::valueTreePropertyChanged (ValueTree& vt, const Identifier& property){
    if (registeredIdentifiersMap.containsValue(property)){
        send(property,vt[property]);
    }
}

bool OSCController::addSender(const Server& srv){
    lastSubscriberAnnounce[srv] = Time::getCurrentTime();
    
    if (senders.count(srv)){
        // The server was already registered as sender. This can happen if the client doesn't disconnect before reconnecting.
        return false;
    }
    return senders[srv].connect(srv.ip, srv.port);
}

bool OSCController::removeSender(const Server& srv){
    if (senders.count(srv)==0 ){
        // The server was not registered as sender. This can happen if the server is interrupted when clients are still connected.
        return false;
    }
    if(!senders[srv].disconnect()){
        std::cerr << "Error: cannot disconnect from " << srv.ip << " on port " << srv.port << std::endl;
        jassertfalse;
        return false;
    }
    senders.erase(srv);
    return true;
}

void OSCController::startBroadcast(){
    mode = SERVER;
    serverBroadcast = std::make_unique<OSCServerBroadcast>(announceAddress,receiverPort);
    
    /* Register to listen for requests */
    registerIdentifier(subscribeIdentifier);
    registerIdentifier(unsubscribeIdentifier);
    registerIdentifier(getIdentifier);
    
    /* Check for expired subscriptions */
    startTimerHz(1);
}

void OSCController::determineLocalIP(const Server& srv){
    
    /* Determine local IP */
    IPAddress serverIpAddr = IPAddress(srv.ip);
    auto ipArray = IPAddress::getAllAddresses();
    int mostLikelyIdx = 0;
    int mostLikelyScore = 0;
    for (auto idx = 0; idx < ipArray.size(); idx++){
        auto ip = ipArray[idx];
        int score = 0;
        while (ip.address[score] == serverIpAddr.address[score])
            score ++;
        if (score > mostLikelyScore){
            mostLikelyScore = score;
            mostLikelyIdx = idx;
        }
    }
    localIp = ipArray[mostLikelyIdx];
    
}

bool OSCController::subscribe(){
    if (senders.size()!=1){
        jassertfalse;
        return false;
    }
    for (auto &&sender : senders){
        determineLocalIP(sender.first);
    }
    const Server srv({localIp.toString(),receiverPort});
    send(subscribeIdentifier, srv);
    mode = CLIENT;
    
    /* Refresh subscription */
    startTimerHz(1);
    return true;
}

bool OSCController::unsubscribe(){
    if (senders.size()!=1){
        jassertfalse;
        return false;
    }
    const Server srv({localIp.toString(),receiverPort});
    send(unsubscribeIdentifier, srv);
    stopTimer();
    return true;
}

int OSCController::getReceiverPort() const{
    return receiverSocket.getBoundPort();
}

/**
 Refresh subscription (CLIENT) or check for expred subscriptions (SERVER)
 */
void OSCController::timerCallback(){
    
    switch (mode){
        case SERVER:{
            std::list<Server> expiredServers;
            const Time now = Time::getCurrentTime();
            for (auto lsa : lastSubscriberAnnounce){
                if ((now - lsa.second).inSeconds() > subscriptionExpiration){
                    expiredServers.push_back(lsa.first);
                }
            }
            for (auto tbd: expiredServers){
                lastSubscriberAnnounce.erase(tbd);
                removeSender(tbd);
            }
            break;
        }
        case CLIENT:{
            const Server srv({localIp.toString(),receiverSocket.getBoundPort()});
            send(subscribeIdentifier, srv);
            break;
        }
        default:
            jassertfalse;
    }
}

bool OSCController::startReceiver(){
    
    while (receiverSocket.getBoundPort()==-1 && !receiverSocket.bindToPort(receiverPort) && (receiverPort!=BROADCAST_PORT))
        receiverPort++;
    if (receiverPort==BROADCAST_PORT){
        std::cerr << "Error: cannot find a free port to listen on" << std::endl;
        jassertfalse;
        return false;
    }
    if (!receiver.connectToSocket(receiverSocket)){
        std::cerr << "Error: cannot listen on port " << receiverSocket.getBoundPort() << std::endl;
        jassertfalse;
        return false;
    }
    for (auto it = registeredIdentifiersMap.begin(); it != registeredIdentifiersMap.end(); ++it)
        receiver.addListener(this,it.getKey());
    
    receiverEnabled = true;
    return true;
}

bool OSCController::stopReceiver(){
    
    if (!receiver.disconnect()){
        std::cerr << "Error: cannot disconnect receiver" << std::endl;
        jassertfalse;
        return false;
    }
    receiver.removeListener(this);
    
    return true;
    
}

void OSCController::send(const Identifier& id, const Server& srv){
    const String address = oscPrefix+id;
    OSCMessage msg(address);
    msg.addString(srv.ip);
    msg.addInt32(srv.port);
    for (auto &sender: senders){
        sender.second.send(msg);
    }
}

void OSCController::send(const Identifier& id, const var& val){
    const String address = oscPrefix+id;
    OSCMessage msg(address);
    if(val.isInt()){
        msg.addInt32(val);
    }else if(val.isDouble()){
        msg.addFloat32(val);
    }else if(val.isBool()){
        msg.addInt32(val);
    }else if (val.isBinaryData()){
        msg.addBlob(*val.getBinaryData());
    }else{
        jassertfalse;
    }
    for (auto &sender: senders){
        sender.second.send(msg);
    }
}

} /* end namespace juce */
