// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file StreamCipher.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 *
 */

#ifndef CRYPTOPALS_STREAMCIPHER_H
#define CRYPTOPALS_STREAMCIPHER_H
#include "Cipher.h"

template <class CIPHER_TYPE>
class StreamCipher {
public:
    StreamCipher() : cipher(CIPHER_TYPE()) {}

    void init(CipherOperationMode mode, AlgorithmParameters* parameters) {
        cipher.init(mode, parameters);
    }

    SecureVector<uint8_t> stream(const SecureVector<uint8_t>& octet_stream);
private:
    CIPHER_TYPE cipher;
};

template <class CIPHER_TYPE>
SecureVector<uint8_t> StreamCipher<CIPHER_TYPE>::stream(const SecureVector<uint8_t>& octet_stream) {
    return cipher.final(octet_stream);
}

#endif //CRYPTOPALS_STREAMCIPHER_H
