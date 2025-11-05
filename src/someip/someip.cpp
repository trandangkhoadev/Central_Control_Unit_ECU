#include "someip/someip.hpp"
#include <iostream>


SomeIPMgr& SomeIPMgr::getInstance()
{
    static SomeIPMgr instance; 
    std::cout << "SomeIPMgr::getInstance"<< std::endl; 
    return instance;
}