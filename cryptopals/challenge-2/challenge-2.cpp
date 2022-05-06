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
#include <RepeatingKeyParameter.h>
#include <StreamCipher.h>
#include <vector>
#include <XORCipher.h>

int main() {
    auto a = HexUtil::toBytes("1c0111001f010100061a024b53535009181c");
    auto b = HexUtil::toBytes("686974207468652062756c6c277320657965");

    auto cipher = StreamCipher<XORCipher>();
    auto keyParam = RepeatingKeyParameter(b);
    cipher.init(CipherOperationMode::ENCRYPT, &keyParam);

    auto c = cipher.stream(a);

    std::cout << HexUtil::toHexString(c) << std::endl;
    return 0;
}