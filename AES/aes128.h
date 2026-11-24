#include <cstdint>
#include <iostream>

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

void subBytes (uint8_t matrix[4][4])
{
    

}