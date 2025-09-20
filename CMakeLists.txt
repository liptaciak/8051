cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(8051 LANGUAGES C)

add_executable(8051 
    src/main.c
    src/cpu.c
    src/memory.c
    src/instructions.c
)

target_sources(8051 PRIVATE
    src/instructions/nop.c
)

target_include_directories(8051 PRIVATE include)