// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file challenge-3.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Contains the solution for Set 1 Challenge 3
 */
#include <algorithm>
#include <Cryptanalysis.h>
#include <cstdint>
#include <format>
#include <HexUtil.h>
#include <iostream>

int main() {
    auto ciphertext = HexUtil::toBytes("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");

    auto [key, score, plaintext] = Cryptanalysis::single_byte_key_attack(ciphertext, Cryptanalysis::english_probability_score);

    std::cout << std::format("{:.3f}, Key: {:#02x}: ", score, key) << std::string(plaintext.begin(), plaintext.end())
              << std::endl;
    return 0;
}