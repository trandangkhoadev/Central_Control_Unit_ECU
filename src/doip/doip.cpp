#include "doip/doip.hpp"


#define DOIP_UDP_PORT 13400
#define DOIP_TCP_PORT 13400

DoIPMgr& DoIPMgr::getInstance()
{
    static DoIPMgr instance; 
    return instance;
}
