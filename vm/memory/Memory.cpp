#include "vm/memory/Memory.hpp"

#include <cstring>

namespace phantom {

Memory::Memory(std::size_t size_bytes)
    : memory_(size_bytes, 0u) {
}

void Memory::reset() {
    std::memset(memory_.data(), 0, memory_.size());
}

void Memory::resize(std::size_t size_bytes) {
    if (size_bytes <= memory_.size()) {
        return;
    }
    memory_.resize(size_bytes, 0u);
}

std::size_t Memory::size() const {
    return memory_.size();
}

std::uint8_t Memory::readByte(std::uint32_t address) const {
    if (address >= memory_.size()) {
        return 0u;
    }
    return memory_[address];
}

void Memory::writeByte(std::uint32_t address, std::uint8_t value) {
    if (address >= memory_.size()) {
        return;
    }
    memory_[address] = value;
}

std::uint32_t Memory::readWord(std::uint32_t address) const {
    std::uint32_t value = 0u;
    for (std::size_t i = 0; i < 4; ++i) {
        const std::uint32_t byte_index = address + static_cast<std::uint32_t>(i);
        if (byte_index >= memory_.size()) {
            break;
        }
        value |= static_cast<std::uint32_t>(memory_[byte_index]) << (i * 8u);
    }
    return value;
}

void Memory::writeWord(std::uint32_t address, std::uint32_t value) {
    for (std::size_t i = 0; i < 4; ++i) {
        const std::uint32_t byte_index = address + static_cast<std::uint32_t>(i);
        if (byte_index >= memory_.size()) {
            break;
        }
        memory_[byte_index] = static_cast<std::uint8_t>((value >> (i * 8u)) & 0xFFu);
    }
}

void Memory::loadProgram(const std::vector<std::uint32_t>& words, std::uint32_t start_address) {
    for (std::size_t i = 0; i < words.size(); ++i) {
        writeWord(start_address + static_cast<std::uint32_t>(i) * 4u, words[i]);
    }
}

std::vector<std::uint8_t> Memory::bytes() const {
    return memory_;
}

} // namespace phantom
