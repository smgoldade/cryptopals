// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file RepeatingKeyParameter.cpp
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Contains the implementation of the RepeatingKeyParameter class
 */

#include "RepeatingKeyParameter.h"

uint8_t RepeatingKeyParameter::getKeyByte(int idx) const {
    return key[idx % key.size()];
}

RepeatingKeyParameter::~RepeatingKeyParameter() = default;
