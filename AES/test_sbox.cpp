#include "aes128.h"
int main() {
    std::cout << std::hex << (int)sbox(0x11) << std::endl; // 82
    std::cout << std::hex << (int)sbox(0x53) << std::endl; // ed
    std::cout << std::hex << (int)sbox(0x00) << std::endl; // 63
    return 0;
}