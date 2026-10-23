# PHANTOM Architecture

PHANTOM is divided into layers so each subsystem can be built, debugged and tested independently.

## Layers

1. PHANTOM Studio
   - VM window
   - terminal
   - debugger
   - memory monitor

2. PHANTOM VM
   - instruction execution
   - devices
   - timers
   - interrupt dispatch

3. PHANTOM CPU (P32)
   - general-purpose registers
   - ALU
   - privilege bits
   - exception state

4. PHANTOM OS Kernel
   - scheduler
   - memory manager
   - processes
   - filesystem

5. Userland
   - shell
   - utilities
   - applications

## Execution model

The host program does not execute OS logic directly. It creates a guest machine and runs guest instructions inside the VM. If the guest kernel hangs, the guest CPU stops or loops in the same way as a real system.

## P32 design principles

- 32-bit address space
- fixed instruction width
- explicit registers and flags
- page-based memory isolation
- a clean privilege boundary between kernel and user mode
- deterministic instruction execution for debugging
