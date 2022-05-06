// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file challenge-1.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Contains the solution for Set 1 Challenge 1
 */
#include <Base64.h>
#include <format>
#include <iostream>

int main() {
    SecureString encoded = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    auto decoded = Base64::decode(encoded);
    for(auto i : decoded) {
        std::cout << std::format("{:02x}", i);
    }
    std::cout << std::endl;

    auto reencoded = Base64::encode(decoded);
    std::cout << reencoded << std::endl;
    return 0;
}