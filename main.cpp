#include <iostream>
#include "someip/someip.hpp"

int main()
{
    SomeIPMgr::getInstance();
    std::cout << "test main" << std::endl; 
}