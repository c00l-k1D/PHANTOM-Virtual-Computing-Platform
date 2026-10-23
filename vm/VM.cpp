#include "vm/VM.hpp"

namespace phantom {

Machine::Machine(std::size_t ram_bytes)
    : memory_(ram_bytes), cpu_() {
    reset();
}

void Machine::reset() {
    memory_.reset();
    cpu_.reset();
    cpu_.setStackPointer(static_cast<std::uint32_t>(memory_.size()) - 16u);
}

void Machine::loadProgram(const std::vector<std::uint32_t>& instructions, std::uint32_t start_address) {
    const std::size_t required_size = static_cast<std::size_t>(start_address) + instructions.size() * sizeof(std::uint32_t) + 16u;
    if (required_size > memory_.size()) {
        memory_.resize(required_size);
    }

    memory_.loadProgram(instructions, start_address);
    cpu_.reset();
    cpu_.setProgramCounter(start_address);
    cpu_.setStackPointer(static_cast<std::uint32_t>(memory_.size()) - 16u);
}

bool Machine::run() {
    for (std::size_t i = 0; i < 100000u; ++i) {
        if (cpu_.halted()) {
            return true;
        }
        if (!cpu_.step(memory_)) {
            return false;
        }
    }
    return false;
}

bool Machine::step() {
    if (cpu_.halted()) {
        return false;
    }
    return cpu_.step(memory_);
}

Cpu& Machine::cpu() {
    return cpu_;
}

Memory& Machine::memory() {
    return memory_;
}

} // namespace phantom
