// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file RepeatingKeyParameter.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines a RepeatingKeyParameter class, which is a simple AlgorithmParameters that simply provides the key
 * over and over in a reptitive fashion. e.g. If the key is "ICE" it will provide "ICEICEICEICE..."
 */

#ifndef _REPEATINGKEYPARAMETER_H_
#define _REPEATINGKEYPARAMETER_H_
#include <cstdint>
#include <utility>
#include <vector>
#include "AlgorithmParameters.h"
#include "Secure.h"

class RepeatingKeyParameter : public AlgorithmParameters {
public:
    explicit RepeatingKeyParameter(SecureVector<uint8_t> repeating_key) : key(std::move(repeating_key)) {};
    ~RepeatingKeyParameter() override;
    uint8_t getKeyByte(int idx) const override;
private:
    std::vector<uint8_t, SecureAllocator<uint8_t>> key;
};

#endif //_REPEATINGKEYPARAMETER_H_
