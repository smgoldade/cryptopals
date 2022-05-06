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
#include "Secure.h"

class HexUtil {
public:
    static SecureString toHexString(const SecureVector<uint8_t>& input);
    static SecureVector<uint8_t> toBytes(const SecureString& input);
};

#endif //CRYPTOPALS_HEXUTIL_H