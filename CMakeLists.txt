cmake_minimum_required(VERSION 3.10)  # 设置所需的最低CMake版本

project(websocket-agent)  # 设置项目名称

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)