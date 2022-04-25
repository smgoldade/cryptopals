#include <Base64.h>
#include <format>
#include <iostream>
#include <vector>

int main() {
    std::string encoded = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    auto decoded = Base64::decode(encoded);
    for (auto i : decoded) {
        std::cout << std::format("{:02x}", i);
    }
    std::cout << std::endl;

    auto reencoded = Base64::encode(decoded);
    std::cout << reencoded << std::endl;
    return 0;
}