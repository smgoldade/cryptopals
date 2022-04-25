// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file challenge-2.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Contains the solution for Set 1 Challenge 2
 */

#include <cstdint>
#include <HexUtil.h>
#include <iostream>
#include <vector>

int main() {
    std::vector<uint8_t> a = HexUtil::toBytes("1c0111001f010100061a024b53535009181c");
    std::vector<uint8_t> b = HexUtil::toBytes("686974207468652062756c6c277320657965");

    std::vector<uint8_t> c;
    for (auto i = 0; i < a.size(); i++) {
        c.push_back(a[i] ^ b[i]);
    }

    std::cout << HexUtil::toHexString(c) << std::endl;
    return 0;
}