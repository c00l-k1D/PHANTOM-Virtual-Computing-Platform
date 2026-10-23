# Executable Format

The executable format for PHANTOM programs is intentionally simple in the first revision.

## Current format

- a flat binary image
- code is placed at a fixed load address
- instructions are 32-bit words in native P32 endianness
- the VM loads the image into guest memory and starts executing from the entry address

## Proposed ELF-like layout

In the future, PHANTOM may adopt a custom object format similar to ELF:

- header
- section table
- .text
- .data
- .rodata
- .bss
- symbol table

The current repository implements the runtime core required to execute raw P32 machine code, while the assembler and linker are still to be added.
