#pragma once

#include <cstdint>
#include <vector>

#include "vm/cpu/Cpu.hpp"
#include "vm/memory/Memory.hpp"

namespace phantom {

class Machine {
public:
    explicit Machine(std::size_t ram_bytes = 1024 * 1024);

    void reset();
    void loadProgram(const std::vector<std::uint32_t>& instructions, std::uint32_t start_address = 0x1000u);
    bool run();
    bool step();

    Cpu& cpu();
    Memory& memory();

private:
    Memory memory_;
    Cpu cpu_;
};

} // namespace phantom
