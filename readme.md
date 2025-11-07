# CPU simulator

This project aims to be a simple simulator of a processor!

---

### Here's a view about each component in it:

- [`cpu.h`](./include/cpu.h): header file that contains implementation of some
variables and functions used in logic.

  - it defined a struct containing:

    - `memory` array with 256 bytes
    - `pc` (Processor Counter) to represent the current position of an
    instruction
    - `acc` (Accumulator) to store results from past operations
    - `addr` to be used in code

- [`cpu.c`](./src/cpu.c): file that contains the main logic.

  - `int run_program(const char *path, const char *mode)`: the only function
  used.

    - the function expected for a binary file (a program) that will be read and
      copied to memory; this block of code do it:

      ```c
      int read = fread(buffer, 1, 16, file);
      while (read > 0) {
          memcpy(c.memory + offset, buffer, read);
          offset += read;
          read = fread(buffer, 1, 16, file);
      }
      ```

      - a temporary array is created to store 16 bytes from the file and to be
      copied into memory.

      - the code is using an [`example file`](./tests/program.bin). You can
      change it for another one!

      ---

> [!WARNING]
> ensure that it respects the following structure:

      ```text
      [OPCODE] [OPERAND] 0xFF (at the final)
      ```

      ---

    - now, the main loop is defined to run while there's valid opcodes in memory
      array:

      - in each iteration, the opcode index is always be the current one
      (current `c.pc` value).

      - the `switch - case` structure is to verify which is the current opcode:

        - `0x01 - LOAD`: catches the value of `c.memory[c.pc]` and use it as an
        index of `memory` array to define `acc` value.

        - `0x02 - LOADI`: instead of pass an address as the operand, we can pass
          a value immediately.

        - `0x03 - STORE`: stores a value in `c.memory[c.pc]` using `c.acc`.

        - `0x04 - OUT`: prints the value of a memory index passed as the
        operand.

        - `0xFF - HILT`: stops the loop.

---

### How to run it?

Uses the [`MAKEFILE`](./Makefile):

- compile all files:

```bash
make all
```

- run the [`main.c`](./src/main.c) file:

```bash
make run
```

- clean build files:

```bash
make clean
```

---

That's it!

