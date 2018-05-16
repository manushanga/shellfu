cmake_minimum_required(VERSION 2.8)

project(shellfu)
add_executable(${PROJECT_NAME} "console.cpp" "command.cpp" "commandbuffer.cpp" "main.cpp")
