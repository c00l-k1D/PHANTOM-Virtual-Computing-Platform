# Memory Model

The virtual machine exposes a linear address space with a configurable physical memory size. The initial design uses a 32-bit virtual address width and a 4 KiB page size.

## Goals

- protect processes from one another
- separate kernel and user memory regions
- allow page faults and memory protection exceptions
- provide predictable debugging visibility for memory inspection

## High-level plan

- physical memory is allocated by the VM and tracked by the memory manager
- virtual memory is mapped through page tables controlled by PTBR
- kernel pages are isolated from user pages
- invalid access attempts generate exceptions through CAUSE and EPC

## Initial implementation

The current VM prototype intentionally keeps the memory model simple and deterministic:

- memory is a contiguous byte array
- load/store instructions operate on 8-bit and 32-bit words
- stack grows downward from the end of RAM
- protection and paging logic are planned for the next phase
