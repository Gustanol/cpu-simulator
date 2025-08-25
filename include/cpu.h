#ifndef CPU_H
#define CPU_H

#include <stdint.h>

struct cpu {
    unsigned char memory[256];
    unsigned char pc;
    unsigned char acc;
    unsigned char addr;
};

int run_program(const char *path, const char *mode);

#endif /* ifndef CPU_H                                                                             \
#define CPU_H */
