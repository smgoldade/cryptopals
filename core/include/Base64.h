#ifndef CRYPTOPALS_BASE64_H
#define CRYPTOPALS_BASE64_H
#include <cstdint>
#include <string>
#include <vector>

class Base64 {
public:
    static const char PADDING = '=';
    static std::string encode(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> decode(const std::string& input);
private:
    static char lookup[64];
};

#endif //CRYPTOPALS_BASE64_H