// Copyright (c) 2022 by Steven Goldade
// This code is licensed under the MIT License, see LICENSE in the root directory for more info.

/**
 * @file Cryptanalysis.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Implements the Cryptanalysis class
 */
#include <Cryptanalysis.h>

const double Cryptanalysis::ENGLISH_PROBABILITIES[26] = {
    0.0834, // A
    0.0154, // B
    0.0273, // C
    0.0414, // D
    0.1260, // E
    0.0203, // F
    0.0192, // G
    0.0611, // H
    0.0671, // I
    0.0023, // J
    0.0087, // K
    0.0424, // L
    0.0253, // M
    0.0680, // N
    0.0770, // O
    0.0166, // P
    0.0009, // Q
    0.0568, // R
    0.0611, // S
    0.0937, // T
    0.0285, // U
    0.0106, // V
    0.0234, // W
    0.0020, // X
    0.0204, // Y
    0.0006, // Z
};
const double Cryptanalysis::ENGLISH_SAMPLE_AVERAGE = 1.0 / 26.0;

double Cryptanalysis::english_probability_score(const std::vector<uint8_t>& input) {
    uint64_t total = input.size();
    uint64_t total_valid = 0;
    uint64_t counts[26] = {0};

    for(auto c : input) {
        c = toupper(c);
        if(c >= 'A' && c <= 'Z') {
            total_valid++;
            counts[c - 'A']++;
        }
        if(c == ' ' || c == '.' || c == '!' || c == '?') {
            total_valid++;
        }
    }

    auto corr_num = 0.0;
    auto corr_d1 = 0.0;
    auto corr_d2 = 0.0;
    for(auto i = 0; i < 26; i++) {
        auto probability = (double)counts[i] / (double)total_valid;
        // Do a simple correlation. Note that we are assuming the valid characters are the only
        // ones that appeared and that normally the sample average would actually be the ideal
        // instead of the actual.
        corr_num += (probability - 1 / 30.0f) * (ENGLISH_PROBABILITIES[i] - ENGLISH_SAMPLE_AVERAGE);
        corr_d1 += (probability - 1 / 30.0f) * (probability - 1 / 30.0f);
        corr_d2 += (ENGLISH_PROBABILITIES[i] - ENGLISH_SAMPLE_AVERAGE)
                   * (ENGLISH_PROBABILITIES[i] - ENGLISH_SAMPLE_AVERAGE);
    }

    // correlation with letter incidence
    double corr = (corr_num / sqrt(corr_d1 * corr_d2));
    corr *= corr;

    // valid english character to character ratio
    double valid_ratio = (double)total_valid / (double)total;

    // we give the valid ratio twice as much weight as we do the correlation with character frequency
    return (corr + valid_ratio * 2) / 3.0;
}

