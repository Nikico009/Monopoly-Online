cmake_minimum_required(VERSION 3.16)
project(MonopolyMultiplayer C CXX)

# Compiler options (standard of C and C++)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


# Allow CMake to find the header files in the src directory
include_directories(src src/menu src/game_client src/game_host)

add_executable(monopoly_app
    src/main.c
    src/menu/menu.c
    src/menu/menu_graphics.c
    src/game_client/game_client.c
    src/game_client/game_client_graphics.c
    src/game_host/game_host.c
)

# 4. Link external libraries
target_link_libraries(monopoly_app PRIVATE raylib)