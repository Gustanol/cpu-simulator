#ifndef CPU_H
#define CPU_H

#include <stdint.h>

struct cpu {
    int16_t memory[256];
    int8_t pc;
    int8_t acc;
    int8_t addr;
};

int run_program(const char *path, const char *mode);

#endif /* ifndef CPU_H                                                                             \
#define CPU_H */
