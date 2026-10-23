#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace phantom {

class Memory {
public:
    explicit Memory(std::size_t size_bytes);

    void reset();
    void resize(std::size_t size_bytes);
    std::size_t size() const;

    std::uint8_t readByte(std::uint32_t address) const;
    void writeByte(std::uint32_t address, std::uint8_t value);

    std::uint32_t readWord(std::uint32_t address) const;
    void writeWord(std::uint32_t address, std::uint32_t value);

    void loadProgram(const std::vector<std::uint32_t>& words, std::uint32_t start_address = 0x1000u);
    std::vector<std::uint8_t> bytes() const;

private:
    std::vector<std::uint8_t> memory_;
};

} // namespace phantom
