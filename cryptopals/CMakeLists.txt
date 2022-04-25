CMAKE_MINIMUM_REQUIRED(VERSION 3.21)
project(cryptopals)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(../core cmake-core)
add_subdirectory(challenge-1)
add_subdirectory(challenge-2)