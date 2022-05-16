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
#include <algorithm>
#include <array>
#include <Cryptanalysis.h>
#include <StreamCipher.h>
#include <XORCipher.h>
#include <iostream>
#include <format>

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

double Cryptanalysis::english_probability_score(const SecureVector<uint8_t>& input) {
    uint64_t total = input.size();
    uint64_t total_valid = 0;
    uint64_t counts[26] = {0};

    for(auto c : input) {
        c = (uint8_t)toupper(c);
        if(c >= 'A' && c <= 'Z') {
            total_valid++;
            counts[c - 'A']++;
        }
        if(c == ' ' || c == '.' || c == '!' || c == '?') {
            total_valid++;
        }
    }

    auto corr_n = 0.0;
    auto corr_d1 = 0.0;
    auto corr_d2 = 0.0;
    for(auto i = 0; i < 26; i++) {
        // Do a simple correlation. Note that we are assuming the valid characters are the only
        // ones that appeared and that normally the sample average would actually be the ideal
        // instead of the actual.
        auto prob_mean_adj = 0.0;
        if(total_valid != 0) {
            prob_mean_adj = ((double)counts[i] / (double)total_valid) - (1.0 / 30.0);
        }
        auto engl_mean_adj = ENGLISH_PROBABILITIES[i] - ENGLISH_SAMPLE_AVERAGE;
        corr_n += prob_mean_adj * engl_mean_adj;
        corr_d1 += prob_mean_adj * prob_mean_adj;
        corr_d2 += engl_mean_adj * engl_mean_adj;
    }

    // correlation with letter incidence
    double corr_d = corr_d1 * corr_d2;
    double corr = 0;
    if(corr_d != 0) {
        corr = (corr_n * corr_n) / corr_d;
    }

    // valid english character to character ratio
    double valid_ratio = (double)total_valid / (double)total;

    // we give the valid ratio twice as much weight as we do the correlation with character frequency
    return (corr + 2 * valid_ratio) / 3.0;
}

double Cryptanalysis::index_of_coincidence(const SecureVector<uint8_t>& input) {
    auto histogram = std::array<int, 256>();

    for(auto& i : input) {
        histogram[i]++;
    }
    auto ioc_n = 0;
    auto ioc_d = 0;
    for(auto& i : histogram) {
        ioc_n += i * (i - 1);
        ioc_d += i;
    }

    if(ioc_d == 0) {
        return 0;
    }
    return (double)ioc_n / (double)(ioc_d * (ioc_d - 1)) * 256;
}

double Cryptanalysis::entropy(const SecureVector<uint8_t>& input) {
    auto histogram = std::array<int, 256>();

    for(auto& i : input) {
        histogram[i]++;
    }
    auto entropy = 0.0;
    for(auto& i : histogram) {
        auto p = i / (double)input.size();
        if(p > 0) {
            entropy -= (p * log2(p));
        }
    }
    return entropy;
}

int Cryptanalysis::hamming_distance(const SecureVector<uint8_t>& a, const SecureVector<uint8_t>& b) {
    int dist = 0;

    auto len = std::min(a.size(), b.size());
    for(auto i = 0; i < len; i++) {
        dist += std::popcount<uint8_t>(a[i] ^ b[i]);
    }
    return dist;
}

std::tuple<uint8_t, double, SecureVector<uint8_t>>
Cryptanalysis::single_byte_key_attack(const SecureVector<uint8_t>& input, analysis_function func) {
    auto secure_input = SecureVector<uint8_t>(input.begin(), input.end());

    auto results = std::vector<std::tuple<uint8_t, double, SecureVector<uint8_t>>>();
    for(auto key = 0; key < 256; key++) {
        auto cipher = StreamCipher<XORCipher>();
        auto rk = RepeatingKeyParameter({static_cast<uint8_t>(key)});
        cipher.init(CipherOperationMode::DECRYPT, &rk);

        auto result = cipher.stream(secure_input);
        auto corr = func(result);

        results.emplace_back(static_cast<uint8_t>(key), corr, result);
    }

    std::sort(
        results.begin(),
        results.end(),
        [](const std::tuple<uint8_t, double, SecureVector<uint8_t>>& a, const std::tuple<uint8_t, double, SecureVector<uint8_t>>& b) {
            return std::get<1>(a) > std::get<1>(b);
        }
    );

    return results[0];
}

std::tuple<SecureVector<uint8_t>, SecureVector<uint8_t>>
Cryptanalysis::known_length_xor_key_attack(const SecureVector<uint8_t>& input, const int& key_length, analysis_function func) {
    auto key = SecureVector<uint8_t>();

    auto split_ciphertext = std::vector<SecureVector<uint8_t>>();
    for(auto i = 0; i < key_length; i++) {
        split_ciphertext.emplace_back();
    }
    for(auto i = 0; i < input.size(); i++) {
        split_ciphertext[i % key_length].emplace_back(input[i]);
    }
    for(auto& i : split_ciphertext) {
        auto [key_b, v, plaintext] = Cryptanalysis::single_byte_key_attack(i, func);
        key.emplace_back(key_b);
    }

    auto cipher = StreamCipher<XORCipher>();
    auto rk = RepeatingKeyParameter(key);
    cipher.init(CipherOperationMode::DECRYPT, &rk);

    auto plaintext = cipher.stream(input);

    return {key, plaintext};
}

int Cryptanalysis::estimate_xor_key_length(const SecureVector<uint8_t>& input, const int& min_key_length, const int& max_key_length) {
    // The estimated XOR key length comes splitting the input into blocks of an estimated key size,
    // and computing the normalized Hamming Distance between all of those blocks and averaging them.
    // This works on the assumption our plaintext has less entropy than random
    // When comparing with the correct key length, we have wt(b_1 xor b_2), which will have a lower Hamming Distance due to existing structure.
    // When comparing with the incorrect key length, we have wt(b_1 xor k_1 xor b_2 xor k_2), which will be random,
    //     and have an expected Hamming Distance of 4bits/byte.
    // Because of this, by getting all the weights and selecting the one with the smallest distance, we are expected to select the correct key length.

    auto key_dict = std::vector<std::tuple<int, double>>();
    for(auto key_size = min_key_length; key_size < max_key_length; key_size++) {
        auto blocks = std::vector<SecureVector<uint8_t>>();
        if(key_size > input.size() / 2) {
            break;
        }

        auto block_count = input.size() / key_size;
        for(auto i = 0; i < block_count; i++) {
            blocks.emplace_back(input.begin() + key_size * i, input.begin() + key_size * (i + 1));
        }

        auto sum = 0.0;
        auto compares = 0;
        for(auto i = 0; i < block_count; i++) {
            for(auto j = i + 1; j < block_count; j++) {
                sum += Cryptanalysis::hamming_distance(blocks[i], blocks[j]);
                compares++;
            }
        }

        key_dict.emplace_back(key_size, sum / (double)(compares * key_size));
    }

    std::sort(
        key_dict.begin(),
        key_dict.end(),
        [](std::tuple<int, double> a, std::tuple<int, double> b) {
            return std::get<1>(a) < std::get<1>(b);
        }
    );

    return std::get<0>(key_dict[0]);
}
