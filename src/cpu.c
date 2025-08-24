#include "cpu.h"
#include <stdint.h>
#include <stdio.h>

int run_program(const char *path, const char *mode) {
    FILE *file;
    struct cpu c;

    file = fopen(path, mode);
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    fread(c.memory, 2, 16, file);
    c.pc = -1;
    int running = 1;

    while (running) {
        int16_t opcode = c.memory[c.pc++];
        switch (opcode) {
        case 0x01:
            c.addr = c.memory[c.pc++];
            c.acc = c.memory[c.addr];
            break;
        case 0x02:
            c.acc = c.memory[c.pc++];
            break;
        case 0x03:
            c.addr = c.memory[c.pc++];
            c.memory[c.addr] = c.acc;
            break;
        case 0x04:
            c.addr = c.memory[c.pc++];
            printf("%c", c.memory[c.addr]);
            break;
        default:
            printf("Invalid opcode!\n");
            running = 0;
            break;
        }
    }
    return 0;
}
