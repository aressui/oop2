cmake_minimum_required(VERSION 3.10)

# Настройка проекта
project(lab_02 
    VERSION 1.0.0
    DESCRIPTION "Лабораторная работа 2: Класс Five с Правилом пяти"
    LANGUAGES CXX
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Статическая линковка для MinGW
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# Настройка директорий
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

# Поиск исходных файлов библиотеки
file(GLOB_RECURSE LIBRARY_SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

# Создание библиотеки
add_library(lab_02_lib ${LIBRARY_SOURCES})

# === Основная программа ===
add_executable(lab_02_main main.cpp)

# Связывание библиотеки с исполняемым файлом
target_link_libraries(lab_02_main PRIVATE lab_02_lib)

# Настройка компилятора (опционально) - ИСПРАВЛЕНО: перенесено после создания lab_02_main
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_02_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(lab_02_main PRIVATE -Wall -Wextra -Wpedantic)
endif()

# === Настройка GoogleTest ===
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Для MinGW важно отключить shared CRT
set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# === Юнит-тесты ===
add_executable(lab_02_tests ${TEST_DIR}/test.cpp)

# Связывание тестов с библиотекой и gtest
target_link_libraries(lab_02_tests PRIVATE lab_02_lib gtest_main)

# Настройка компилятора для тестов
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(lab_02_tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Для MinGW: копируем необходимые DLL
if(MINGW)
    add_custom_command(TARGET lab_02_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:gtest>"
        $<TARGET_FILE_DIR:lab_02_tests>
    )
    add_custom_command(TARGET lab_02_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:gtest_main>"
        $<TARGET_FILE_DIR:lab_02_tests>
    )
endif()

include(GoogleTest)
gtest_discover_tests(lab_02_tests)