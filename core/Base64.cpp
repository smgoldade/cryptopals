// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/**
 * @file Base64.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Implements the Base64 class
 */
#include <stdexcept>
#include "include/Base64.h"

char Base64::lookup[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                         'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                         'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                         'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                         'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                         'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                         'w', 'x', 'y', 'z', '0', '1', '2', '3',
                         '4', '5', '6', '7', '8', '9', '+', '/'};

SecureString Base64::encode(const SecureVector<uint8_t>& input) {
    auto encoded = SecureString();

    for(auto i = 0; i < input.size(); i += 3) {
        auto pad_1 = i + 2 >= input.size();
        auto pad_2 = i + 1 >= input.size();

        auto a = input[i];
        if(!pad_1 && !pad_2) {
            auto b = input[i + 1];
            auto c = input[i + 2];
            encoded.push_back(lookup[a >> 2]);
            encoded.push_back(lookup[((a & 0x03) << 4) + (b >> 4)]);
            encoded.push_back(lookup[((b & 0x0F) << 2) + (c >> 6)]);
            encoded.push_back(lookup[c & 0x3F]);
        } else if(pad_1 && !pad_2) {
            auto b = input[i + 1];
            encoded.push_back(lookup[a >> 2]);
            encoded.push_back(lookup[((a & 0x03) << 4) + (b >> 4)]);
            encoded.push_back(lookup[((b & 0x0F) << 2)]);
            encoded.push_back(PADDING);
        } else {
            encoded.push_back(lookup[a >> 2]);
            encoded.push_back(lookup[(a & 0x03) << 4]);
            encoded.push_back(PADDING);
            encoded.push_back(PADDING);
        }
    }
    return encoded;
}

SecureVector<uint8_t> Base64::decode(const SecureString& input) {
    auto decode = SecureVector<uint8_t>();

    uint8_t working = 0;
    enum {
        CLEAN,
        HIGH_6,
        HIGH_4,
        HIGH_2
    } state = CLEAN;
    for(char c : input) {
        auto val = -1;
        for(auto i = 0; i < 64; i++) {
            if(lookup[i] == c) {
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
            working = (uint8_t)(val << 2);
            state = HIGH_6;
            break;
        case HIGH_6:
            decode.push_back(working + ((val & 0x30) >> 4));
            working = (val & 0x0F) << 4;
            state = HIGH_4;
            break;
        case HIGH_4:
            decode.push_back(working + ((val & 0x3C) >> 2));
            working = (val & 0x03) << 6;
            state = HIGH_2;
            break;
        case HIGH_2:
            decode.push_back((uint8_t)(working + val));
            working = 0;
            state = CLEAN;
            break;
        default:
            // should be unreachable
            throw std::logic_error("Invalid Base64::decode state");
        }
    }
    return decode;
}
