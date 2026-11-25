#include "aes128.h"
int main () {
    uint8_t input[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x11};
    uint8_t key[16] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t matrix[4][4];
    uint8_t roundkey[4][4];

    input_to_matrix(matrix, input);
    print_matrix(matrix);
    input_to_matrix(roundkey, key);
    addRoundkey(matrix, roundkey);
    std::cout << "AddRoundKey:" << std::endl;
    print_matrix(matrix);

    subBytes(matrix);
    std::cout << "SubBytes:" << std::endl;
    print_matrix(matrix);

    ShiftRows(matrix);
    std::cout << "ShiftRows:" << std::endl;
    print_matrix(matrix);

    // MixColumns(matrix);
    // std::cout << "MixColumns:" << std::endl;
    // print_matrix(matrix);

    return 0;
}