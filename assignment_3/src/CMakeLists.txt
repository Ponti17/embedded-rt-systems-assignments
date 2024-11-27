cmake_minimum_required(VERSION 3.10)

# Project name
project(EmbeddedSystemX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    embeddedSystemX.cpp
    states.cpp
    main.cpp
    commands.cpp
)

# Add the executable
add_executable(embedded_system_x ${SOURCES})
