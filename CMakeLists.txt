cmake_minimum_required(VERSION 3.10)  # 设置所需的最低CMake版本

project(websocket-agent)  # 设置项目名称

# 添加可执行文件
add_executable(${PROJECT_NAME} 
                main.cpp
                src/reactor/reactor.cpp
                src/reactor/channel.cpp
                src/reactor/epollPoller.cpp)

# 引入头文件目录
target_include_directories(${PROJECT_NAME} 
                            PRIVATE ${CMAKE_SOURCE_DIR}/src/base
                            PRIVATE ${CMAKE_SOURCE_DIR}/src/reactor)