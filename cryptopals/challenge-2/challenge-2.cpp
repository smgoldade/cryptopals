#include <cstdint>
#include <HexUtil.h>
#include <vector>
#include <iostream>

int main() {
    std::vector<uint8_t> a = HexUtil::toBytes("1c0111001f010100061a024b53535009181c");
    std::vector<uint8_t> b = HexUtil::toBytes("686974207468652062756c6c277320657965");

    std::vector<uint8_t> c;
    for (auto i = 0; i < a.size(); i++) {
        c.push_back(a[i] ^ b[i]);
    }

    std::cout << HexUtil::toHexString(c) << std::endl;
    return 0;
}