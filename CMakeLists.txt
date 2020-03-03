cmake_minimum_required(VERSION 3.15)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 14)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        DesignByContract.h
        tinystr.h
        tinyxml.h
        TicTacToeUtils.h
        TicTacToe.h
        TicTacToeImporter.h

        tinystr.cpp
        tinyxml.cpp
        tinyxmlerror.cpp
        tinyxmlparser.cpp
        TicTacToeUtils.cpp
        TicTacToe.cpp
        TicTacToeImporter.cpp
        TicTacToeExporter.cpp
        TicTacToeMain.cpp)

add_executable(TicTacToeMain ${RELEASE_SOURCE_FILES})

# Set source files for TEST target
set(TEST_SOURCE_FILES
        DesignByContract.h
        tinystr.h
        tinyxml.h
        TicTacToeUtils.h
        TicTacToe.h
        TicTacToeImporter.h

        tinystr.cpp
        tinyxml.cpp
        tinyxmlerror.cpp
        tinyxmlparser.cpp
        TicTacToeUtils.cpp
        TicTacToe.cpp
        TicTacToeImporter.cpp
        TicTacToeExporter.cpp
        TicTacToeTests.cpp)

# Create TEST target
add_executable(TicTacToeTests ${TEST_SOURCE_FILES})


# googletest subproject
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
# Specify that Tests relies on "gtest" Link library
target_link_libraries(TicTacToeTests gtest)
