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
#include <HexUtil.h>
#include <iostream>
#include <vector>
#include <format>

int main() {
    auto cipher = HexUtil::toBytes("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");

    std::vector<std::tuple<double, uint8_t, std::vector<uint8_t>>> results;
    for (auto key = 0; key < 256; key++) {
        std::vector<uint8_t> result;

        for (auto i : cipher) {
            result.push_back(i ^ key);
        }

        double corr = Cryptanalysis::englishProbabilityScore(result);
        results.emplace_back(corr, key, result);
    }

    std::sort(
            results.begin(),
            results.end(),
            [](const std::tuple<double, uint8_t, std::vector<uint8_t>>& a,
                    const std::tuple<double, uint8_t, std::vector<uint8_t>>& b) {
                return std::get<0>(a) > std::get<0>(b);
            }
    );

    std::cout << std::format("{:.3f}, Key: {:#02x}: ", std::get<0>(results[0]), std::get<1>(results[0]))
              << std::string(std::get<2>(results[0]).begin(), std::get<2>(results[0]).end()) << std::endl;

    return 0;
}