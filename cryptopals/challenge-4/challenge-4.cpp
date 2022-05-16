// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file challenge-4.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Contains the solution for Set 1 Challenge 4
 */
#include <algorithm>
#include <Cryptanalysis.h>
#include <format>
#include <fstream>
#include <HexUtil.h>
#include <iostream>
#include <string>
#include <vector>
#include <Cipher.h>
#include <StreamCipher.h>
#include <XORCipher.h>

int main() {
    // I know, a relative path. Good luck!
    std::ifstream input("../../challenge-4/input.txt");
    if(!input.is_open()) {
        std::cerr << "Unable to open input.txt";
        return -1;
    }

    SecureString line;
    uint64_t line_number = 0;
    std::vector<std::tuple<double, uint8_t, uint64_t, SecureVector<uint8_t>>> results;

    std::vector<std::vector<uint8_t>> hexes;
    while(std::getline(input, line)) {
        auto hex = HexUtil::toBytes(line);

        for(auto key = 0; key < 256; key++) {
            auto cipher = StreamCipher<XORCipher>();
            auto rk = RepeatingKeyParameter({static_cast<uint8_t>(key)});
            cipher.init(CipherOperationMode::ENCRYPT, &rk);

            auto result = cipher.stream(hex);
            auto prob = Cryptanalysis::english_probability_score(result);
            results.emplace_back(prob, static_cast<uint8_t>(key), line_number, result);
        }
        line_number++;
    }

    std::sort(
        results.begin(),
        results.end(),
        [](const std::tuple<double, uint8_t, uint64_t, SecureVector<uint8_t>>& a,
           const std::tuple<double, uint8_t, uint64_t, SecureVector<uint8_t>>& b) {
            return std::get<0>(a) > std::get<0>(b);
        }
    );

    std::cout << std::format("{:.3f}, Key: {:#02x}, Line: {:d}: ", std::get<0>(results[0]), std::get<1>(results[0]),
                             std::get<2>(results[0]))
              << std::string(std::get<3>(results[0]).begin(), std::get<3>(results[0]).end()) << std::endl;
    return 0;
}