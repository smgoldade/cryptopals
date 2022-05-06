// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file XORCipher.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 *
 */

#ifndef _XORCIPHER_H_
#define _XORCIPHER_H_

#include "Cipher.h"
#include "RepeatingKeyParameter.h"

class XORCipher : Cipher {
public:
    void init(CipherOperationMode md, AlgorithmParameters* param) override;
    void partial(SecureVector<uint8_t> octet_stream) override;
    SecureVector<uint8_t> final(SecureVector<uint8_t> octet_stream) override;
private:
    const AlgorithmParameters* parameters;
    std::vector<uint8_t, SecureAllocator<uint8_t>> buffer;
};

#endif //_XORCIPHER_H_
