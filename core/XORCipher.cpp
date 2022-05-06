// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file XORCipher.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 *
 */
#include "XORCipher.h"

void XORCipher::init(CipherOperationMode md, AlgorithmParameters* param) {
    this->parameters = param;
}

void XORCipher::partial(SecureVector<uint8_t> octet_stream) {
    buffer.insert(buffer.end(), octet_stream.begin(), octet_stream.end());
}

SecureVector<uint8_t> XORCipher::final(SecureVector<uint8_t> octet_stream) {
    partial(octet_stream);

    auto out = SecureVector<uint8_t>();
    for(auto i = 0; i < buffer.size(); i++) {
        out.push_back(buffer[i] ^ parameters->getKeyByte(i));
    }
    return out;
}
