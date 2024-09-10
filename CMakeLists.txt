#
# Copyright 2021 Xilinx Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

# cmake needs this line
cmake_minimum_required(VERSION 3.5)

# Define project name
project(ddr-qos)

SET(CMAKE_INSTALL_PREFIX $ENV{OECORE_TARGET_SYSROOT})
set(CMAKE_C_STANDARD 99)

include_directories(include)
file(GLOB SOURCES "src/*.c")
SET(INSTALL_PATH "bin")

#set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR})
# Declare the executable target built from your sources
add_executable(ddr-qos ${SOURCES})
install(TARGETS ddr-qos RUNTIME DESTINATION ${INSTALL_PATH})

set(VERSION "1.0")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_NAME "ddr-qos")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "anil.mamidala@amd.com")
set(CPACK_PACKAGE_VENDOR "xilinx")
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "arm64")
set(CPACK_RPM_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_RPM_SPEC_MORE_DEFINE "%define _build_id_links none")
include(CPack)
