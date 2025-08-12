cmake_minimum_required(VERSION 3.20)
project(CalcBusStopOccupLCL)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
endif()

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(LIBLCL_DIR "${CMAKE_SOURCE_DIR}/libs/liblcl")
set(LIBLCL_DLL "${LIBLCL_DIR}/liblcl.dll")  # Полный путь к DLL


if(NOT EXISTS "${LIBLCL_DLL}")
    message(FATAL_ERROR "DLL file not found: ${LIBLCL_DLL}")
endif()

# Создание исполняемого файла
add_executable(CalcBusStopOccupLCL main.cpp
        MainForm.cpp
        MainForm.h
        libs/liblcl/liblcl.c
        libs/liblcl/liblcl.h)

if(WIN32)
    add_custom_command(
            TARGET CalcBusStopOccupLCL POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${LIBLCL_DLL}"
            "$<TARGET_FILE_DIR:CalcBusStopOccupLCL>"
            COMMENT "Copying liblcl.dll to output directory"
            VERBATIM
    )
    target_link_libraries(CalcBusStopOccupLCL "${LIBLCL_DLL}")
endif()