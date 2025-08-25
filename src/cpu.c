#include "cpu.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int run_program(const char *path, const char *mode) {
    /*
     * variables setup
     */
    FILE *file;         // file variable
    struct cpu c;       // defining struct from cpu.h
    uint8_t buffer[16]; // creating an array to store 16 bytes to form memory in blocks
    int offset = 0;     // current line of the binary file

    /*
     * initialization of the variables from the struct
     */
    c.pc = 0;
    c.addr = 0;
    c.acc = 0;

    int running = 1; // variable to initialize the "infinite" loop

    /*
     * opens a file using the expected parameters and saves it on file variable
     */
    file = fopen(path, mode);
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    /*
     * read 16 bytes at a time and saves into buffer array
     *
     * in each iteration, copy buffer into c.memory array
     */
    int read = fread(buffer, 1, 16, file);
    while (read > 0) {
        memcpy(c.memory + offset, buffer, read);
        offset += read;
        read = fread(buffer, 1, 16, file);
    }

    while (running) {
        /*
         * opcode refers to an instruction
         *
         * it is followed by an operand
         */
        int16_t opcode = c.memory[c.pc++];
        switch (opcode) {
        case 0x01: // LOAD
            c.addr = c.memory[c.pc++];
            c.acc = c.memory[c.addr];
            break;
        case 0x02: // LOADI
            c.acc = c.memory[c.pc++];
            break;
        case 0x03: // STORE
            c.addr = c.memory[c.pc++];
            c.memory[c.addr] = c.acc;
            break;
        case 0x04: // OUT
            c.addr = c.memory[c.pc++];
            printf("%c", c.memory[c.addr]);
            break;
        case 0xFF: // HILT
            running = 0;
            break;
        case 0x20: // SPACE (in ASCII)
            printf(" ");
            break;
        default:
            printf("\n%x: Invalid opcode!\n", opcode);
            running = 0;
            break;
        }
    }
    printf("\n");
    fclose(file);
    return 0;
}
