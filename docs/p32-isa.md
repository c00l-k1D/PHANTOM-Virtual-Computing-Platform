# P32 ISA Specification

P32 is a compact custom 32-bit ISA designed to support a small but complete operating system.

## Registers

- R0..R15: 16 general-purpose 32-bit registers
- PC: program counter
- SP: stack pointer
- FP: frame pointer
- FLAGS: arithmetic and comparison flags
- CR0: CPU mode and control bits
- PTBR: page table base register
- CAUSE: interrupt or exception cause
- EPC: exception return address

R0 is treated as a constant zero register.

## Instruction format

All instructions are 32 bits wide.

- Bits 31..24: opcode
- Bits 23..20: destination register
- Bits 19..16: source register 1
- Bits 15..12: source register 2 or immediate selector
- Bits 11..0: immediate value or offset

## Core instructions

### Arithmetic and logic

- MOVI
- ADD
- SUB
- MUL
- DIV
- AND
- OR
- XOR
- NOT
- SHL
- SHR

### Memory

- LD
- ST
- LDB
- STB

### Control flow

- JMP
- BEQ
- BNE
- BLT
- CALL
- RET

### CPU control

- HALT
- EI
- DI
- IRET
- TRAP
- SYSCALL

## Example

```asm
.section .text
.global _start

_start:
    MOVI R1, 40
    MOVI R2, 2
    ADD  R3, R1, R2

    MOVI R4, 0x10000000
    ST   R3, [R4]

    HALT
```

The repository currently contains the machine-level encoding helpers and runtime execution model used by the VM. The assembler and link tools are planned as the next step in the toolchain roadmap.
