/*
    This project used to simulate the application of Central control unit ECU
    - SomeIP (Vehicle protocol - comminucation with another ECU in vehicle)
    - Doip (Vehicle diagnostic protocol)
    - MQTT

*/

/* Development step and challenging
- Create project, add Cmake, build script, minimal source code
    -> cmake .. didn't work, trying to using cmake -G "MinGW Makefiles" .. and have to install mingw32-make

- clone vsomeip via https://github.com/GENIVI/vsomeip.git
    -> cmake -G "MinGW Makefiles" .. didn't work, need to install boost lib
    Solition: download boost lib https://www.boost.org/releases/latest/
        build bootlib
            .\boostrap gcc -> after build successfully, the b2 file appearance
            .\b2 toolset=gcc --with-system --with-thread --with-filesystem link=static runtime-link=static variant=release -j4
            -> after build successfully the boostxxxx.a
    -> Build vsomeip to libraries .a
        

- when copy boost into /lib folder, if in the CMakeLists.txt have the line
    file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/main.cpp)
        GLOB_RECURSE will find all of file .cpp in the main.cpp path -> build 
        -> fix the keyword to  GLOB
        

*/