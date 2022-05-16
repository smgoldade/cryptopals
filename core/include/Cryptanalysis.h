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
#include "Secure.h"
#include <string>
#include <vector>

typedef double (* analysis_function)(const SecureVector<uint8_t>&);

class Cryptanalysis {
public:
    static const double ENGLISH_PROBABILITIES[26];
    static const double ENGLISH_SAMPLE_AVERAGE;

    /**
     * @param input a vector containing the data to be analyzed
     * @return a value representing the input data's probability score of being English.
     */
    static double english_probability_score(const SecureVector<uint8_t>& input);

    /**
     * @param input a vector containing the data to be analyzed
     * @return  the normalized index of coincidence for the provided vector.
     */
    static double index_of_coincidence(const SecureVector<uint8_t>& input);

    /**
     * @param input the input vector to calculate the entropy for
     * @return the entropy of the given vector
     */
    static double entropy(const SecureVector<uint8_t>& input);

    /**
     * @param a
     * @param b
     * @return computes the Hamming Distance between two input octet vectors, up to the minimum length of the two
     */
    static int hamming_distance(const SecureVector<uint8_t>& a, const SecureVector<uint8_t>& b);

    /**
     * @param input the input ciphertext to attack
     * @param func an analysis function to score data by. Higher scores are considered better.
     * @return a tuple containing the key byte, the analysis score, and resulting plaintext
     */
    static std::tuple<uint8_t, double, SecureVector<uint8_t>> single_byte_key_attack(const SecureVector<uint8_t>& input, analysis_function func);

    /**
     * @param input the input ciphertext to attack
     * @param key_length the known key length
     * @param func an analysis function to score data by. Higher scores are considered better.
     * @return a tuple containing the key and the plaintext
     */
    static std::tuple<SecureVector<uint8_t>, SecureVector<uint8_t>>
    known_length_xor_key_attack(const SecureVector<uint8_t>& input, const int& key_length, analysis_function func);

    /**
     * Uses normalized Hamming Distance to estimate the most probable key length within the given range.
     * This assumes the plaintext has less entropy than random causing normalized Hamming Distance to be
     * less than 0.5 (purely random).
     * @param input the input ciphertext
     * @param min_key_length the minimum key size to use
     * @param max_key_length the maximum key size to use
     * @return the most probable key size for the given data within the allowed range
     */
    static int estimate_xor_key_length(const SecureVector<uint8_t>& input, const int& min_key_length, const int& max_key_length);
};

#endif //CRYPTOPALS_CRYPTANALYSIS_H