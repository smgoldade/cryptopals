# Copyright (C) 2022 by Steven Goldade
# This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.
CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
project(cryptopals)

set(CMAKE_CXX_STANDARD 23)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif ()

add_subdirectory(../core cmake-core)
add_subdirectory(challenge-1)
add_subdirectory(challenge-2)
add_subdirectory(challenge-3)
add_subdirectory(challenge-4)
add_subdirectory(challenge-5)
add_subdirectory(challenge-6)