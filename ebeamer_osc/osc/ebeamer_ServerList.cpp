/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

ServerList::ServerList(){
    /* Start timer to check for inactive servers */
    startTimer(timerPeriod*1000);
}

ServerList::~ServerList(){
    
}

void ServerList::setValueTree(ValueTree vt){
    valueTree=vt;
}

void ServerList::setIdentifier(const Identifier& ident){
    identifier=ident;
}


void ServerList::addOrUpdate(const Server& srv){
    
    GenericScopedLock<SpinLock> l(lock);
    
    if (servers.count(srv)==0){
        /* Add new server */
        servers[srv] = ++lastServerId;
        updateValueTree();
    }else{
        /* Renew timestamp of existing server */
        auto srvId = servers[srv];
        servers.erase(srv);
        servers[srv] = srvId;
    }
    
}

void ServerList::timerCallback(){
    /* Remove inactive servers */
    {
        GenericScopedLock<SpinLock> l(lock);
        /* Check expired announces */
        auto now = Time::getCurrentTime();
        std::list<Server> toBeRemoved;
        for (auto server : servers)
            if ((now - server.first.lastAnnounce).inSeconds() > timeout)
                toBeRemoved.push_back(server.first);
        if (toBeRemoved.size()){
            for (auto server : toBeRemoved){
                servers.erase(server);
            }
            updateValueTree();
        }
    }
    
}

void ServerList::updateValueTree(){
    /* Update value tree by setting the property */
    Array<var> srvArray;
    for (auto srv : servers){
        Array<var> srvSpec;
        srvSpec.add(srv.first.ip);
        srvSpec.add(srv.first.port);
        srvSpec.add(srv.second); // server id
        srvArray.add(srvSpec);
    }
    valueTree.setProperty(identifier, srvArray, nullptr);
}

} /* end namespace juce */
