#include "aes128.h"
int main() {
    std::cout << std::hex << (int)sbox(0x11) << std::endl;
    return 0;
}