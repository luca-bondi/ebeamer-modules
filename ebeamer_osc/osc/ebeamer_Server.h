/*
  ==============================================================================

 Ebeamer OSC module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce{

struct JUCE_API Server{
    String ip;
    int32 port;
    Time lastAnnounce = Time::getCurrentTime();
    
    bool operator< (const Server& other) const{
        return (ip < other.ip) | ((ip  ==  other.ip) && (port < other.port));
    };
    
    friend bool operator== (const Server& rhs, const Server& lhs){
        return (rhs.ip  ==  lhs.ip) && (rhs.port == lhs.port);
    };
    
    friend std::ostream& operator<<(std::ostream& os, const Server& obj){
        os << obj.ip << ":" << obj.port;
        return os;
    };
    
    const String toString() const{
        return ip + ":" + String(port);
    }
};

} /* end namespace juce */
