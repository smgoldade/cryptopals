# Copyright (C) 2022 by Steven Goldade
# This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.
project(core)

add_library(core STATIC)
target_include_directories(core PUBLIC include)
target_sources(core PRIVATE Base64.cpp Cryptanalysis.cpp HexUtil.cpp)