cmake_minimum_required(VERSION 3.10)

project(EmbeddedSystemX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    embeddedSystemX.cpp
    states.cpp
    main.cpp
    commands.cpp
    RealTimeLoopModes.cpp
)

add_executable(embedded_system_x ${SOURCES})
