// Copyright (c) 2022 by Steven Goldade
// This code is licensed under the MIT License, see LICENSE in the root directory for more info.

/**
 * @file Cryptanalysis.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines the Cryptanalysis class, which has various functions designed to help during the analysis
 * of various different cryptographic routines.
 */

#ifndef CRYPTOPALS_CRYPTANALYSIS_H
#define CRYPTOPALS_CRYPTANALYSIS_H

#include <cstdint>
#include <string>
#include <vector>

class Cryptanalysis {
public:
    static const double ENGLISH_PROBABILITIES[26];
    static const double ENGLISH_SAMPLE_AVERAGE;

    /**
     * @param input a vector containing the data to be analyzed
     * @return a value representing the input data's probability score of being English.
     */
    static double english_probability_score(const std::vector<uint8_t>& input);
};

#endif //CRYPTOPALS_CRYPTANALYSIS_H