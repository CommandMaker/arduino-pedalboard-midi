cmake_minimum_required(VERSION 3.5)

project(MIDI-control-software)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libs/rtmidi)

add_subdirectory(src)