#include <cstdint>
#include <iostream>
#include "gf28.h"

void input_to_matrix
(uint8_t matrix[4][4], uint8_t input[16]) { // chuyen input 16 byte sang ma tran 4x4
    for (int cols = 0; cols  < 4; cols ++) {
        for (int rows = 0; rows < 4; rows++) {
            matrix[rows][cols] = input[cols * 4 + rows];
        }
    }
}

void matrix_to_output
(uint8_t output[16], uint8_t matrix[4][4]) { // chuyen ma tran 4x4 sang output 16 byte
    for (int cols = 0; cols < 4; cols++) {
        for (int rows = 0; rows < 4; rows++) {
            output[cols * 4 + rows] = matrix[rows][cols];
        }
    }
}   

void print_matrix
(uint8_t matrix[4][4]) { // in ma tran 4x4 theo hexa16
    for (int rows = 0; rows < 4; rows++) {
        for (int cols = 0; cols < 4; cols++) {
            std::cout << std::hex << (int)matrix[rows][cols] << " ";
        }
        std::cout << std::endl;
    }
}

void addRoundkey
(uint8_t matrix[4][4], uint8_t roundkey[4][4]) { // XOR ma tran input voi roundkey 128 bit
    for (int cols = 0; cols < 4; cols++) {
        for (int rows = 0; rows < 4; rows++) {
            matrix[rows][cols] ^= roundkey[rows][cols];
        }
    }
}

uint8_t sbox(uint8_t a) {
    uint8_t b = inverse(a);

    int b_bits[8];
    int c[8] = {1, 1, 0, 0, 0, 1, 1, 0}; // vector c
    int y[8] = {0};
    
    // chuyen b sang dang bit array
    int temp = b;
    for (int i = 0; i < 8; i++) {
        b_bits[i] = temp & 1;
        temp >>= 1;
    }
    
    // dung cong thuc y = A.x^-1 + c
    for (int i = 0; i < 8; i++) {
        y[i] = b_bits[i] 
            ^ b_bits[(i + 4) % 8] 
            ^ b_bits[(i + 5) % 8] 
            ^ b_bits[(i + 6) % 8] 
            ^ b_bits[(i + 7) % 8] 
            ^ c[i];
    }
    
    // ghep cac bit y_array lai thanh 1 byte uint8_t
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result = result | (y[i] << i);
    }
    return static_cast<uint8_t>(result);
}

void subBytes(uint8_t input[4][4]) {
    for (int cols = 0; cols < 4; cols++)
    {
        for (int rows = 0; rows < 4; rows++)
        {
            input[rows][cols] = sbox(input[rows][cols]);
        }
    }
}

void ShiftRows(uint8_t state[4][4])
{
    uint8_t temp[4];
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            state[row][col] = state[(col - row + 4) % 4][col];
        }
    }
}

void MixColumns(uint8_t state[4][4]) {
    uint8_t temp[4][4];
    for (int cols = 0; cols < 4; cols++) {
        temp[0][cols] = multiple(0x02, state[0][cols])
            ^ multiple(0x03, state[1][cols])
            ^ state[2][cols]
            ^ state[3][cols];
        temp[1][cols] = state[0][cols]
            ^ multiple(0x02, state[1][cols])
            ^ multiple(0x03, state[2][cols])
            ^ state[3][cols];
        temp[2][cols] = state[0][cols]
            ^ state[1][cols]
            ^ multiple(0x02, state[2][cols]);
        temp[3][cols] = multiple(0x03, state[0][cols])
            ^ state[1][cols]
            ^ state[2][cols]
            ^ multiple(0x02, state[3][cols]);
    }
    for (int cols = 0; cols < 4; cols++) {
        for (int rows = 0; rows < 4; rows++) {
            state[rows][cols] = temp[rows][cols];
        }
    }
}

