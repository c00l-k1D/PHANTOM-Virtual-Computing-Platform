# System Calls and Exceptions

System calls are an important boundary between user code and kernel code.

## Goals

- provide a stable ABI for user programs
- isolate privileged operations inside the kernel
- allow trap-based and syscall-based communication

## Initial kernel model

The first version of PHANTOM will provide a lightweight model where:

- SYSCALL triggers a guest-controlled kernel transition
- TRAP is used for explicit exception-like events
- IRET resumes execution after a handled exception
- CAUSE stores the reason for a trap
- EPC stores the return address for the interrupted instruction

This is enough to establish the principle without yet introducing a full user-space ABI.
