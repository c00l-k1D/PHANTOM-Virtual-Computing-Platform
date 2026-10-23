cmake_minimum_required(VERSION 3.16)

project(PHANTOM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(phantom_vm
    vm/VM.cpp
    vm/cpu/Cpu.cpp
    vm/memory/Memory.cpp
)

target_include_directories(phantom_vm
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

enable_testing()
add_executable(cpu_tests tests/cpu/test_cpu.cpp)
target_link_libraries(cpu_tests PRIVATE phantom_vm)
add_test(NAME cpu_tests COMMAND cpu_tests)
