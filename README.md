# PHANTOM — Virtual Computing Platform

PHANTOM is a minimal but realistic virtual computing platform built around a custom 32-bit architecture named P32.

The project follows a layered design:

- PHANTOM Studio: user interface and debugging tools
- PHANTOM VM: execution engine, devices, timers and MMU concepts
- PHANTOM CPU: P32 core with registers, instruction decoder and ALU
- PHANTOM OS Kernel: scheduler, memory manager, processes and system calls
- Userland: shell, tools and applications

This repository intentionally starts with the lowest layer: a working P32 CPU model and a programmatic way to assemble and run machine code.

## Architecture goals

- 32-bit instruction set and addressing model
- byte-addressable virtual memory
- explicit CPU privilege and exception states
- a clear separation between guest VM state and host code
- reproducible unit tests for the CPU and memory model

## Build

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Current status

The initial implementation includes:

- custom P32 instruction encoding helpers
- a CPU model with register file and execution loop
- a memory model with 32-bit loads/stores
- a VM wrapper for running machine code
- a CPU test suite verifying arithmetic and branching behavior

## Quick example

```cpp
#include "vm/VM.hpp"
#include "vm/isa.hpp"

using namespace phantom;

Machine machine(1024 * 1024);
machine.loadProgram({
    p32::make_imm(p32::Opcode::MOVI, 1, 0, 40),
    p32::make_imm(p32::Opcode::MOVI, 2, 0, 2),
    p32::make_r3(p32::Opcode::ADD, 3, 1, 2),
    p32::make_imm(p32::Opcode::HALT, 0, 0, 0)
});

machine.run();
```

## Planned roadmap

1. CPU Core
2. Toolchain
3. Boot and Kernel
4. Memory and Processes
5. PHFS and Userland
6. Studio and Release

See the docs folder for the architectural specification.
