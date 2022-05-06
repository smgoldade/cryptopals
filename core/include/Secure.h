// Copyright (c) 2022 by Steven Goldade
// This file is licensed under the MIT License. Please see the LICENSE file in the root directory for more info.

/****************************************************
 * @file SecureAllocator.h
 * @author Steven Goldade <smgoldade@gmail.com>
 *
 * @section LICENSE
 * Please see LICENSE in the root directory.
 *
 * @section DESCRIPTION
 * Defines a SecureAllocator template that implements the minimal necessary template functions for an allocator
 * that clears memory to 0 before deleting. Secure may be a bit of a misnomer, but the name has stuck.
 *
 * Also adds a SecureString and SecureVector typedef.
 */

#ifndef CRYPTOPALS_CORE_INCLUDE_SECUREALLOCATOR_H
#define CRYPTOPALS_CORE_INCLUDE_SECUREALLOCATOR_H
#include <string>
#include <vector>

template <class T>
struct SecureAllocator {
    typedef T value_type;

    explicit SecureAllocator() noexcept = default;

    template <class U> explicit SecureAllocator(const SecureAllocator<U>&) noexcept {}

    template <class U> bool operator==(const SecureAllocator<U>&) const noexcept {
        return true;
    }

    template <class U> bool operator!=(const SecureAllocator<U>&) const noexcept {
        return false;
    }

    T* allocate(size_t n) const;
    void deallocate(T* p, size_t s) const noexcept;
};

template <class T>
T* SecureAllocator<T>::allocate(const size_t n) const {
    if(n == 0) {
        return nullptr;
    }
    if(n > static_cast<size_t>(-1) / sizeof(T)) {
        throw std::bad_array_new_length();
    }
    auto* pv = new T[n];
    if(!pv) {
        throw std::bad_alloc();
    }
    return pv;
}

template <class T>
void SecureAllocator<T>::deallocate(T* const p, size_t s) const noexcept {
    memset(p, 0, s * sizeof(T));
    delete[] p;
}

template <class T>
using SecureVector = std::vector<T, SecureAllocator<T>>;

template <class T>
std::vector<T> unsafe_vector(SecureVector<T> vector) {
    auto unsafe = std::vector<T>();

    unsafe.insert(unsafe.end(), vector.begin(), vector.end());
    return unsafe;
}

using SecureString = std::basic_string<char, std::char_traits<char>, SecureAllocator<char>>;
#endif //CRYPTOPALS_CORE_INCLUDE_SECUREALLOCATOR_H
