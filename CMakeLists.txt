# cmake needs this line
cmake_minimum_required(VERSION 3.5)

# Define project name
project(ddr-qos)

SET(CMAKE_INSTALL_PREFIX $ENV{OECORE_TARGET_SYSROOT})
set(CMAKE_C_STANDARD 99)

include_directories(include)
file(GLOB SOURCES "src/*.c")
SET(INSTALL_PATH "usr/bin")

#set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})
# Declare the executable target built from your sources
add_executable(ddr-qos ${SOURCES})
install(TARGETS ddr-qos RUNTIME DESTINATION ${INSTALL_PATH})

set(VERSION "1.0")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_NAME "ddr-qos")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "amamidal@xilinx.com")
set(CPACK_PACKAGE_VENDOR "xilinx")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "arm64")
set(CPACK_RPM_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_RPM_SPEC_MORE_DEFINE "%define _build_id_links none")
include(CPack)

