#ifndef AGENT__H
#define AGENT__H

/*
Will send a request to an object to broadcast its changes.
*/
class Agent
{
public:
    
    virtual void requestBroadcast() = 0;
    virtual ~Agent() = default;
};

#endif
