cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(emu8051 LANGUAGES C)

option(USE_GUI "Build GUI version using GTK4" ON)

add_library(emu8051_emulator STATIC
    src/cpu.c
    src/memory.c
    src/instructions.c
    src/instructions/nop.c
    src/instructions/mov.c
)
target_include_directories(emu8051_emulator PUBLIC include)

set(APP_SOURCES
    src/main.c
)

if (USE_GUI)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)

    list(APPEND APP_SOURCES
        src/gui.c
    )

    add_executable(emu8051 ${APP_SOURCES})
    target_link_libraries(emu8051 PRIVATE emu8051_emulator ${GTK4_LIBRARIES})
    target_include_directories(emu8051 PRIVATE include ${GTK4_INCLUDE_DIRS})
    target_compile_options(emu8051 PRIVATE ${GTK4_CFLAGS_OTHER})
    target_compile_definitions(emu8051 PRIVATE USE_GUI)
else()
    add_executable(emu8051 ${APP_SOURCES})
    target_link_libraries(emu8051 PRIVATE emu8051_emulator)
    target_include_directories(emu8051 PRIVATE include)
endif()