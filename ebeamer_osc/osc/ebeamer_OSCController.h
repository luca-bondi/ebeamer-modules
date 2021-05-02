/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/


namespace juce{

class JUCE_API OSCController:
private OSCReceiver::ListenerWithOSCAddress<OSCReceiver::MessageLoopCallback>,
private ValueTree::Listener,
private Timer
{
  
public:
    OSCController();
    ~OSCController();
    
    /** Initialize the controller */
    void init(ValueTree);
    
    /** Initialize the broadcast receiver */
    void initBroadcastReceiver(const Identifier&);
    
    /** Start broadcasting as server*/
    void startBroadcast();
    
    /** Register an identifier.
     When the corresponding value changes, an OSC update is sent to all the recipients
     When an update is received via OSC for the corresponding identifier and the value is updated
     */
    void registerIdentifier(const Identifier& );
    
    /** Unregister identifier */
    void unregisterIdentifier(const Identifier& );
    
    /** Add a new sender */
    bool addSender(const Server&);
    
    /** Remove a sender */
    bool removeSender(const Server&);
    
    /** Bind to a local port and start listening for OSC messages */
    bool startReceiver();
    
    /** Stop listening to OSC messages and release port */
    bool stopReceiver();
    
    /** Subscribe to a server */
    bool subscribe();
    
    /** Unsubscribe from a server */
    bool unsubscribe();
    
    /** Return allocated osc receiver port */
    int getReceiverPort() const;
    
    /** Return last received OSC message Time */
    Time lastMessageReceivedAt() const;
    
private:
    
    enum {
        UNDEF,
        SERVER,
        CLIENT
    }mode;
    
    /** Broadcast sender */
    std::unique_ptr<OSCServerBroadcast> serverBroadcast;
    
    /** Broadcast receiver instance */
    OSCReceiver broadcastReceiver;
    
    /** Broadcast receiver datagram socket */
    DatagramSocket broadcastSocket;
    
    /** Array of active senders */
    std::map<Server, OSCSender> senders;
    
    /** Local IP address for polling/subscription */
    IPAddress localIp;
    
    void determineLocalIP(const Server&);
    
    /** General receiver */
    OSCReceiver receiver;
    
    /** General receiver is listening */
    bool receiverEnabled = false;
    
    /** Socket used to receive OSC messages */
    DatagramSocket receiverSocket;

    /** Active servers list */
    ServerList serverList;
    
    /** Broadcast identifier to store received Ebeamer announce details */
    Identifier serversIdentifier;
    
    /** ValueTree instance */
    ValueTree valueTree;
    
    /** Send a dump of current status */
    void sendDump(const Server&);
    
    /** Timer callback, used to keep subscription active */
    void timerCallback() override;
    
    /** OSC message listener */
    void oscMessageReceived (const OSCMessage&) override;
    
    /** ValueTree listener */
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    
    /** Identifiers registered to be kept synchronized between valueTree and OSC */
    HashMap<String,Identifier> registeredIdentifiersMap;
    
    /** Send a specific value to all the registered receivers */
    void send(const Identifier&, const var&);
    
    /** Send subscribe and unsubscribe messages */
    void send(const Identifier&, const Server&);
    
    /** Receiver port */
    int receiverPort = 9001;
    
    /** Last received message time */
    Time lastReceivedMessageTime = Time::getCurrentTime();
    
    /** Registry of last seen subscribers */
    std::map<Server,Time> lastSubscriberAnnounce;
    
    /** Seconds to wait before declaring subscription expired */
    const float subscriptionExpiration = 3;
    
    /* ======== Constants ======== */
    const Identifier announceIdentifier = "announce";
    const Identifier getIdentifier = "get";
    const String oscPrefix = "/ebeamer/";
    const String announceAddress = oscPrefix + announceIdentifier.toString();
    const String getAddress = oscPrefix + getIdentifier.toString();
    
    
};

}; /* end namespace juce */
