cmake_minimum_required(VERSION 3.18)

## TODO: Rename this
project(SerialCommunication)
add_executable(SerialC)

# Set paths
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Get all cpp files
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

# Add files to target
target_include_directories(SerialC PUBLIC ${SOURCE_DIR})
target_sources(SerialC PUBLIC ${SOURCE_FILES})

