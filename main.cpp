#include <someip/someip.hpp>
#include <iostream>

SomeIPMgr& someIPObj = SomeIPMgr::getInstance();

void handle_signal(int) {
    std::cout << "\n[Main] Caught SIGINT. Stopping server..." << std::endl;
    someIPObj.stop();
    exit(0);
}


int main() {
    std::cout << "[Server] Starting...\n";
    if(someIPObj.init() != true)
    {
        std::cout << "[Server] Initialize error ...\n";
    } 
    return 0;
}