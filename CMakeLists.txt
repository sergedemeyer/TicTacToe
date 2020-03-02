cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES TicTacToe.h TicTacToe.cpp TicTacToeMain.cpp)

add_executable(TicTacToeMain ${RELEASE_SOURCE_FILES})