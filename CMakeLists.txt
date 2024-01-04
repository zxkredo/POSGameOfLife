cmake_minimum_required(VERSION 3.18)
project(POSGameOfLifeClient)

set(CMAKE_CXX_STANDARD 17)

add_executable(POSGameOfLifeClient main.cpp "source files/my_socket.cpp"
        "source files/GameState.cpp"
        headers/GameState.h
)
target_link_libraries(POSGameOfLifeClient wsock32 ws2_32)