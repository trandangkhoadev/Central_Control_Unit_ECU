#include "someip/someip.hpp"
#include <iostream>


SomeIPMgr& SomeIPMgr::getInstance()
{
    static SomeIPMgr instance; 
    return instance;
}