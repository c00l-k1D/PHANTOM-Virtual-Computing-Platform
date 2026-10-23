#include "vm/cpu/Cpu.hpp"

#include <stdexcept>

#include "vm/isa.hpp"
#include "vm/memory/Memory.hpp"

namespace phantom {

namespace {
constexpr std::uint32_t kZeroRegisterIndex = 0u;

std::uint32_t signExtend12(std::uint16_t value) {
    constexpr std::uint16_t mask = 0x800u;
    if ((value & mask) != 0u) {
        return static_cast<std::uint32_t>(value | 0xFFFFF000u);
    }
    return static_cast<std::uint32_t>(value);
}

} // namespace

Cpu::Cpu() {
    reset();
}

void Cpu::reset() {
    registers_.fill(0u);
    pc_ = 0u;
    sp_ = 0u;
    fp_ = 0u;
    flags_ = 0u;
    cr0_ = 0u;
    ptbr_ = 0u;
    cause_ = 0u;
    epc_ = 0u;
    halted_ = false;
}

void Cpu::setProgramCounter(std::uint32_t program_counter) {
    pc_ = program_counter;
}

void Cpu::setStackPointer(std::uint32_t stack_pointer) {
    sp_ = stack_pointer;
}

void Cpu::setFramePointer(std::uint32_t frame_pointer) {
    fp_ = frame_pointer;
}

std::uint32_t Cpu::readRegister(std::size_t index) const {
    if (index >= registers_.size()) {
        throw std::out_of_range("CPU register index out of range");
    }
    return (index == kZeroRegisterIndex) ? 0u : registers_[index];
}

void Cpu::writeRegister(std::size_t index, std::uint32_t value) {
    if (index >= registers_.size()) {
        throw std::out_of_range("CPU register index out of range");
    }
    if (index != kZeroRegisterIndex) {
        registers_[index] = value;
    }
}

std::uint32_t Cpu::pc() const {
    return pc_;
}

std::uint32_t Cpu::sp() const {
    return sp_;
}

std::uint32_t Cpu::fp() const {
    return fp_;
}

std::uint32_t Cpu::flags() const {
    return flags_;
}

bool Cpu::halted() const {
    return halted_;
}

bool Cpu::step(Memory& memory) {
    if (halted_) {
        return false;
    }

    const std::uint32_t instruction = memory.readWord(pc_);
    pc_ += 4u;

    const std::uint8_t opcode = static_cast<std::uint8_t>((instruction >> 24) & 0xFFu);
    const std::uint8_t rd = static_cast<std::uint8_t>((instruction >> 20) & 0x0Fu);
    const std::uint8_t rs1 = static_cast<std::uint8_t>((instruction >> 16) & 0x0Fu);
    const std::uint8_t rs2 = static_cast<std::uint8_t>((instruction >> 12) & 0x0Fu);
    const std::uint16_t imm12 = static_cast<std::uint16_t>(instruction & 0x0FFFu);
    const std::int32_t signed_imm = static_cast<std::int32_t>(signExtend12(imm12));

    switch (static_cast<int>(opcode)) {
        case static_cast<int>(p32::Opcode::NOP):
            break;

        case static_cast<int>(p32::Opcode::MOVI):
            writeRegister(rd, imm12);
            break;

        case static_cast<int>(p32::Opcode::ADD):
            writeRegister(rd, readRegister(rs1) + readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::SUB):
            writeRegister(rd, readRegister(rs1) - readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::MUL):
            writeRegister(rd, readRegister(rs1) * readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::DIV):
            if (readRegister(rs2) == 0u) {
                cause_ = 0x00000004u;
                halted_ = true;
                return false;
            }
            writeRegister(rd, readRegister(rs1) / readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::AND):
            writeRegister(rd, readRegister(rs1) & readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::OR):
            writeRegister(rd, readRegister(rs1) | readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::XOR):
            writeRegister(rd, readRegister(rs1) ^ readRegister(rs2));
            break;

        case static_cast<int>(p32::Opcode::NOT):
            writeRegister(rd, ~readRegister(rs1));
            break;

        case static_cast<int>(p32::Opcode::SHL):
            writeRegister(rd, readRegister(rs1) << (readRegister(rs2) & 31u));
            break;

        case static_cast<int>(p32::Opcode::SHR):
            writeRegister(rd, readRegister(rs1) >> (readRegister(rs2) & 31u));
            break;

        case static_cast<int>(p32::Opcode::LD): {
            const std::uint32_t address = readRegister(rs1) + static_cast<std::uint32_t>(signed_imm);
            writeRegister(rd, memory.readWord(address));
            break;
        }

        case static_cast<int>(p32::Opcode::ST): {
            const std::uint32_t address = readRegister(rs1) + static_cast<std::uint32_t>(signed_imm);
            memory.writeWord(address, readRegister(rd));
            break;
        }

        case static_cast<int>(p32::Opcode::LDB): {
            const std::uint32_t address = readRegister(rs1) + static_cast<std::uint32_t>(signed_imm);
            writeRegister(rd, memory.readByte(address));
            break;
        }

        case static_cast<int>(p32::Opcode::STB): {
            const std::uint32_t address = readRegister(rs1) + static_cast<std::uint32_t>(signed_imm);
            memory.writeByte(address, static_cast<std::uint8_t>(readRegister(rd)));
            break;
        }

        case static_cast<int>(p32::Opcode::JMP):
            pc_ = readRegister(rs1) + static_cast<std::uint32_t>(signed_imm);
            break;

        case static_cast<int>(p32::Opcode::BEQ):
            if (readRegister(rs1) == readRegister(rs2)) {
                pc_ += static_cast<std::uint32_t>(signed_imm * 4);
            }
            break;

        case static_cast<int>(p32::Opcode::BNE):
            if (readRegister(rs1) != readRegister(rs2)) {
                pc_ += static_cast<std::uint32_t>(signed_imm * 4);
            }
            break;

        case static_cast<int>(p32::Opcode::BLT): {
            const std::int32_t lhs = static_cast<std::int32_t>(readRegister(rs1));
            const std::int32_t rhs = static_cast<std::int32_t>(readRegister(rs2));
            if (lhs < rhs) {
                pc_ += static_cast<std::uint32_t>(signed_imm * 4);
            }
            break;
        }

        case static_cast<int>(p32::Opcode::PUSH):
            sp_ -= 4u;
            memory.writeWord(sp_, readRegister(rs1));
            break;

        case static_cast<int>(p32::Opcode::POP):
            writeRegister(rd, memory.readWord(sp_));
            sp_ += 4u;
            break;

        case static_cast<int>(p32::Opcode::CALL): {
            const std::uint32_t target = readRegister(rs1) + static_cast<std::uint32_t>(signed_imm);
            sp_ -= 4u;
            memory.writeWord(sp_, pc_);
            pc_ = target;
            break;
        }

        case static_cast<int>(p32::Opcode::RET):
            pc_ = memory.readWord(sp_);
            sp_ += 4u;
            break;

        case static_cast<int>(p32::Opcode::HALT):
            halted_ = true;
            return false;

        case static_cast<int>(p32::Opcode::EI):
            cr0_ |= 0x00000001u;
            break;

        case static_cast<int>(p32::Opcode::DI):
            cr0_ &= ~0x00000001u;
            break;

        case static_cast<int>(p32::Opcode::IRET):
            pc_ = epc_;
            break;

        case static_cast<int>(p32::Opcode::TRAP):
            cause_ = 0x00000002u;
            halted_ = true;
            return false;

        case static_cast<int>(p32::Opcode::SYSCALL):
            cause_ = 0x00000001u;
            halted_ = true;
            return false;

        default:
            cause_ = 0xFFFFFFFFu;
            halted_ = true;
            return false;
    }

    return true;
}

} // namespace phantom
