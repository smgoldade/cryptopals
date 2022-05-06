// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file HexUtil.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Implements the HexUtil class
 */
#include <stdexcept>
#include "HexUtil.h"

SecureString HexUtil::toHexString(const SecureVector<uint8_t>& input) {
    auto out_string = SecureString();

    for(auto i : input) {
        out_string.push_back("0123456789ABCDEF"[i >> 4]);
        out_string.push_back("0123456789ABCDEF"[i & 0x0F]);
    }

    return out_string;
}

SecureVector<uint8_t> HexUtil::toBytes(const SecureString& input) {
    auto bytes = SecureVector<uint8_t>();

    uint8_t working = 0;
    enum {
        CLEAN,
        HIGH
    } state = CLEAN;
    for(auto c : input) {
        auto val = -1;
        for(auto i = 0; i < 16; i++) {
            if(toupper(c) == "0123456789ABCDEF"[i]) {
                val = i;
                break;
            }
        }

        if(val == -1) {
            // invalid characters are ignored
            continue;
        }

        switch(state) {
        case CLEAN:
            working = val << 4;
            state = HIGH;
            break;
        case HIGH:
            bytes.push_back(working + val);
            state = CLEAN;
            break;
        default:
            // should be unreachable
            throw std::logic_error("Invalid HexUtil::toBytes state");
        }
    }
    return bytes;
}