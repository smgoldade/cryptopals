#ifndef CRYPTOPALS_BASE64_H
#define CRYPTOPALS_BASE64_H
#include <cstdint>
#include <vector>

class Base64 {
public:
    static const char PADDING = '=';
    static std::vector<char> encode(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> decode(const std::vector<char>& input);
private:
    static char lookup[64];
};

#endif //CRYPTOPALS_BASE64_H