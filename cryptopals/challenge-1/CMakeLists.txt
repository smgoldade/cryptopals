# Copyright (C) 2022 by Steven Goldade
# This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.
project(challenge-1)

add_executable(challenge-1)
target_sources(challenge-1 PRIVATE challenge-1.cpp)
target_link_libraries(challenge-1 core)