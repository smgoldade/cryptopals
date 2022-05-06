// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file AlgorithmParameters.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines the AlgorithmParameters class, used to contain parameters used by Ciphers. Basically just a place holder.
 */

#ifndef CRYPTOPALS_ALGORITHMPARAMETERS_H
#define CRYPTOPALS_ALGORITHMPARAMETERS_H

#include <cstdint>

class AlgorithmParameters {
public:
    virtual ~AlgorithmParameters() = default;
    virtual uint8_t getKeyByte(int idx) const = 0;
};

#endif //CRYPTOPALS_ALGORITHMPARAMETERS_H
