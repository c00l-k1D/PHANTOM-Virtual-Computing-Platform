#pragma once

#include <cstdint>

namespace phantom::p32 {

enum class Opcode : std::uint8_t {
    NOP = 0x00,
    MOVI = 0x01,
    ADD = 0x02,
    SUB = 0x03,
    MUL = 0x04,
    DIV = 0x05,

    AND = 0x10,
    OR = 0x11,
    XOR = 0x12,
    NOT = 0x13,
    SHL = 0x14,
    SHR = 0x15,

    LD = 0x20,
    ST = 0x21,
    LDB = 0x22,
    STB = 0x23,

    JMP = 0x30,
    BEQ = 0x31,
    BNE = 0x32,
    BLT = 0x33,

    PUSH = 0x40,
    POP = 0x41,
    CALL = 0x42,
    RET = 0x43,

    HALT = 0x50,
    EI = 0x51,
    DI = 0x52,
    IRET = 0x53,

    TRAP = 0x60,
    SYSCALL = 0x61,
};

inline std::uint32_t make_r3(Opcode op, std::uint8_t rd, std::uint8_t rs1, std::uint8_t rs2) {
    return (static_cast<std::uint32_t>(op) << 24) |
           (static_cast<std::uint32_t>(rd) << 20) |
           (static_cast<std::uint32_t>(rs1) << 16) |
           (static_cast<std::uint32_t>(rs2) << 12);
}

inline std::uint32_t make_imm(Opcode op, std::uint8_t rd, std::uint8_t rs1, std::uint16_t imm) {
    return (static_cast<std::uint32_t>(op) << 24) |
           (static_cast<std::uint32_t>(rd) << 20) |
           (static_cast<std::uint32_t>(rs1) << 16) |
           (static_cast<std::uint32_t>(imm) & 0x0FFFu);
}

inline std::uint32_t make_branch(Opcode op, std::uint8_t rs1, std::uint8_t rs2, std::int16_t offset) {
    return (static_cast<std::uint32_t>(op) << 24) |
           (static_cast<std::uint32_t>(rs1) << 20) |
           (static_cast<std::uint32_t>(rs2) << 16) |
           (static_cast<std::uint32_t>(static_cast<std::uint16_t>(offset)) & 0x0FFFu);
}

} // namespace phantom::p32
