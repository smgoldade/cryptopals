// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file cipher.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines the cipher base class which is designed to be extended for implementation of actual ciphers.
 *
 */

#ifndef CRYPTOPALS_CIPHER_H
#define CRYPTOPALS_CIPHER_H
#include <cstdint>
#include <vector>
#include "AlgorithmParameters.h"
#include "Secure.h"

enum class CipherOperationMode {
    ENCRYPT,
    DECRYPT
};

class Cipher {
    virtual void init(CipherOperationMode mode, AlgorithmParameters* parameters) = 0;
    virtual void partial(SecureVector<uint8_t> octet_stream) = 0;
    virtual SecureVector<uint8_t> final(SecureVector<uint8_t> octet_stream) = 0;
};

#endif //CRYPTOPALS_CIPHER_H
