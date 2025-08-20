#ifndef CPU_H
#define CPU_H

#include <stdint.h>

struct cpu {
    int8_t memory[256];
    int8_t pc;
    int8_t acc;
};

#endif /* ifndef CPU_H                                                                             \
#define CPU_H */
