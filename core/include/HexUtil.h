#ifndef CRYPTOPALS_HEXUTIL_H
#define CRYPTOPALS_HEXUTIL_H
#include <cstdint>
#include <string>
#include <vector>

class HexUtil {
public:
    static std::string toHexString(const std::vector<uint8_t>& input);
    static std::vector<uint8_t> toBytes(const std::string& input);
};

#endif //CRYPTOPALS_HEXUTIL_H