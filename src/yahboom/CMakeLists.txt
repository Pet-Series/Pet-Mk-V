
project(yahboom)

set(CMAKE_CXX_STANDARD 20)

# Set paths
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})

## Yahboom library
add_library(yahboom)

target_include_directories(yahboom
  PUBLIC
    ${SOURCE_DIR}
)

target_sources(yahboom
  PRIVATE
    ${SOURCE_DIR}/SerialCommunication/serial.cpp
    ${SOURCE_DIR}/YahboomCommunication/yahboom.cpp
)

## Communication node
add_executable(yahboom_node)

target_sources(yahboom_node
  PRIVATE
    ${SOURCE_DIR}/yahboom_node.cpp
)

target_link_libraries(yahboom_node
    yahboom
)

ament_target_dependencies(yahboom_node 
    rclcpp
    geometry_msgs
    std_msgs
)

install(TARGETS yahboom_node
    DESTINATION lib/${PROJECT_NAME}
)