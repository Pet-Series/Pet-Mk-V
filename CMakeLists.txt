cmake_minimum_required(VERSION 3.10)

## TODO: Rename this
project(SerialCommunication)
add_executable(SerialC)

# Settings

target_compile_options(SerialC PRIVATE -Wall)
set(CMAKE_CXX_STANDARD 20)

# Set paths
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/arduino)

# Get all cpp files
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

# Add files to target
target_include_directories(SerialC PUBLIC ${SOURCE_DIR})
target_sources(SerialC PUBLIC ${SOURCE_FILES})

