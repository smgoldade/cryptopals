// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file HexUtil.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines the HexUtil class, containing useful functions for dealing with hex strings and the like.
 */
#ifndef CRYPTOPALS_HEXUTIL_H
#define CRYPTOPALS_HEXUTIL_H
#include <cstdint>
#include <string>
#include <vector>

class HexUtil {
public:
    static std::string toHexString(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> toBytes(const std::string& input);
};

#endif //CRYPTOPALS_HEXUTIL_H