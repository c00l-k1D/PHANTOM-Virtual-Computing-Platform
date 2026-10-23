#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace phantom {

class Memory;

class Cpu {
public:
    static constexpr std::size_t GPR_COUNT = 16;

    Cpu();

    void reset();
    void setProgramCounter(std::uint32_t program_counter);
    void setStackPointer(std::uint32_t stack_pointer);
    void setFramePointer(std::uint32_t frame_pointer);

    std::uint32_t readRegister(std::size_t index) const;
    void writeRegister(std::size_t index, std::uint32_t value);

    std::uint32_t pc() const;
    std::uint32_t sp() const;
    std::uint32_t fp() const;
    std::uint32_t flags() const;
    bool halted() const;

    bool step(Memory& memory);

private:
    std::array<std::uint32_t, GPR_COUNT> registers_{};
    std::uint32_t pc_ = 0;
    std::uint32_t sp_ = 0;
    std::uint32_t fp_ = 0;
    std::uint32_t flags_ = 0;
    std::uint32_t cr0_ = 0;
    std::uint32_t ptbr_ = 0;
    std::uint32_t cause_ = 0;
    std::uint32_t epc_ = 0;
    bool halted_ = false;
};

} // namespace phantom
