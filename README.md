# Cryptopals Challenges 
A repository containing my adventure through the [Cryptopals Crypto Challenges](https://cryptopals.com/).

## Notice
There are several self-rolled implementations of cryptographic procedures within. In general, the consensus
in industry is to use tried-and-true publicly available libraries for implementing cryptography, as it
is vital things are well reviewed, tested, and even attacked. 

I make no guarantee the implementations contained herein are cryptographically secure (and in fact some challenges
are intentionally not!)

## Build
Development used Jetbrains CLion referencing MSVC, and can be built with CMake.
The root project is located in the cryptopals sub-directory.
```bash
cd cryptopals
mkdir cmake_build
cd cmake_build
cmake ../cryptopals
cmake --build .
```
