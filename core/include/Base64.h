// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file Base64.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines the Base64 class, used to encode and decode strings to uint8_t and vice versa
 */
#ifndef CRYPTOPALS_BASE64_H
#define CRYPTOPALS_BASE64_H
#include <cstdint>
#include <string>
#include <vector>

class Base64 {
public:
    static const char PADDING = '=';
    static std::string encode(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> decode(const std::string& input);
private:
    static char lookup[64];
};

#endif //CRYPTOPALS_BASE64_H