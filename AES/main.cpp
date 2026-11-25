#include "aes128.h"
#include <iostream>

using namespace std;

int main()
{
    uint8_t input[16] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x11,
        0x00, 0x00, 0x00, 0x11
    };

    uint8_t key[16] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };

    uint8_t state[4][4];
    uint8_t roundkeys[4][4]; 


    input_to_matrix(state, input);
    key_expansion(key);
    addRoundkey(state, roundkeys);

    for (int round = 1; round <= 10; round++) {

        subBytes(state);

        ShiftRows(state);

        // Vòng cuối không có MixColumns
        if (round != 10) {
            MixColumns(state);
        }
        addRoundkey(state, roundkeys);
    }
    print_matrix(state);
}