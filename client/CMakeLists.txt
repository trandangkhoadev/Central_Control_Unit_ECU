cmake_minimum_required(VERSION 3.28.0)

project(Client_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(/home/khoa/cpp_project/k_lib/vsomeip/interface)

file(GLOB SRC_FILES
    ${CMAKE_SOURCE_DIR}/main.cpp
)
link_directories(/home/khoa/cpp_project/k_lib/vsomeip/build)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    vsomeip3
    vsomeip3-sd
    vsomeip3-e2e
    vsomeip3-cfg
    pthread
)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source files found: ${SRC_FILES}")