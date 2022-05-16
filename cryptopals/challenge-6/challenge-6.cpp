// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file challenge-6.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Contains the solution for Set 1 Challenge 6
 */
#include <algorithm>
#include <Base64.h>
#include <cassert>
#include <Cryptanalysis.h>
#include <iostream>
#include <format>
#include <fstream>
#include <RepeatingKeyParameter.h>
#include <Secure.h>
#include <sstream>
#include <StreamCipher.h>
#include <XORCipher.h>

void hamming_distance_test() {
    SecureString a = "this is a test";
    SecureString b = "wokka wokka!!!";
    auto dist = Cryptanalysis::hamming_distance(string_to_vector<uint8_t>(a), string_to_vector<uint8_t>(b));

    if(dist == 37) {
        std::cout << "Hamming distance is: " << std::format("{:d}", dist) << std::endl;
    } else {
        std::cerr << "Hamming distance is: " << std::format("{:d}", dist) << std::endl;
        std::cerr << "Expected 37!" << std::endl;
    }
}

int main() {
    hamming_distance_test();

    // GASP, another relative path! Good luck!
    std::ifstream input("../../challenge-6/input.txt");
    if(!input.is_open()) {
        std::cerr << "Unable to open input.txt";
        return -1;
    }
    std::stringstream buffer;
    buffer << input.rdbuf();

    auto base64_str = SecureString(buffer.str());
    auto ciphertext = Base64::decode(base64_str);

    auto key_length = Cryptanalysis::estimate_xor_key_length(ciphertext, 2, 40);
    auto [key, plaintext] = Cryptanalysis::known_length_xor_key_attack(ciphertext, key_length, Cryptanalysis::english_probability_score);

    std::cout << std::format("Key length {:d}: {:s}\n{:s}", key_length, vector_to_string(key), vector_to_string(plaintext)) << std::endl;

    return 0;
}
