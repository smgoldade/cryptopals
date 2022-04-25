#include <stdexcept>
#include "HexUtil.h"

std::string HexUtil::toHexString(const std::vector<uint8_t>& input) {
    auto hex_string = std::string();

    for (auto i : input) {
        hex_string.push_back("0123456789ABCDEF"[i >> 4]);
        hex_string.push_back("0123456789ABCDEF"[i & 0x0F]);
    }

    return hex_string;
}

std::vector<uint8_t> HexUtil::toBytes(const std::string& input) {
    auto bytes = std::vector<uint8_t>();

    uint8_t working = 0;
    enum {
        CLEAN,
        HIGH
    } state = CLEAN;
    for (auto c : input) {
        auto val = -1;
        for (auto i = 0; i < 16; i++) {
            if (toupper(c) == "0123456789ABCDEF"[i]) {
                val = i;
                break;
            }
        }

        if (val == -1) {
            // invalid characters are ignored
            continue;
        }

        switch (state) {
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
