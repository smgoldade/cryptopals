#include <Base64.h>
#include <format>
#include <iostream>
#include <vector>

int main() {
    std::string encoded = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    auto decoded = Base64::decode(std::vector<char>(encoded.begin(), encoded.end()));
    for (auto i : decoded) {
        std::cout << std::format("{:02x}", i);
    }
    std::cout << std::endl;

    auto reencoded = Base64::encode(decoded);
    auto re_str = std::string(reencoded.begin(), reencoded.end());
    std::cout << re_str << std::endl;
    return 0;
}