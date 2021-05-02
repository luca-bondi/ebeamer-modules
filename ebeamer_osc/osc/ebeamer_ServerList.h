/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

/** Active servers list */
class JUCE_API ServerList:
private Timer
{
    
public:
    ServerList();
    ~ServerList();
    
    void setValueTree(ValueTree);
    void setIdentifier(const Identifier&);
    void addOrUpdate(const Server&);
    
private:
    
    ValueTree valueTree;
    Identifier identifier;
    
    SpinLock lock;
    std::map<Server,int> servers;
    int lastServerId = 0;
    
    /** Update valueTree with the current list of servers */
    void updateValueTree();
    
    /** Timeout before declaring a server inactive [s] */
    const float timeout = 10;
    
    /** Timer period to check for inactive servers [s] */
    const float timerPeriod = 1;
    
    /** Timer callback */
    void timerCallback() override;
    
};

} /* end namespace juce */
