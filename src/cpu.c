#include "cpu.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int run_program(const char *path, const char *mode) {
    FILE *file;
    struct cpu c;
    uint8_t buffer[16];
    int offset = 0;
    c.pc = 0;
    c.addr = 0;
    c.acc = 0;
    int running = 1;

    file = fopen(path, mode);
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    int read = fread(buffer, 1, 16, file);
    while (read > 0) {
        memcpy(c.memory + offset, buffer, read);
        offset += read;
        read = fread(buffer, 1, 16, file);
    }

    /*
    for (int i = 0; i < 256; i++) {
        printf("%x ", c.memory[i]);
    }
    printf("\n");
*/
    while (running) {
        // printf("%d: %x ", c.pc, c.memory[c.pc]);
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
        case 0xFF:
            running = 0;
            break;
        case 0x20:
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
