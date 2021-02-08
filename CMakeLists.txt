# cmake needs this line
cmake_minimum_required(VERSION 3.5)

# Define project name
project(ddr-qos C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
file(GLOB SOURCES "src/*.c")

# Declare the executable target built from your sources
add_executable(ddr-qos ${SOURCES})

