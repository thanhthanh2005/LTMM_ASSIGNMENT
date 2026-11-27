#include "aes128.h"

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
    uint8_t roundkeys[11][4][4]; 

    input_to_matrix(state, input);
    key_expansion(key, roundkeys);
    addRoundkey(state, roundkeys[0]);

    for (int round = 1; round <= 10; round++) {

        subBytes(state);
        ShiftRows(state);

        // Vòng cuối không có MixColumns
        if (round != 10) {
            MixColumns(state);
        }
        addRoundkey(state, roundkeys[round]);
    }
    print_matrix(state);
}