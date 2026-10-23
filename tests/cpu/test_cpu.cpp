#include <cassert>
#include <iostream>
#include <vector>

#include "vm/VM.hpp"
#include "vm/isa.hpp"

int main() {
    using namespace phantom;
    using namespace phantom::p32;

    {
        Machine machine(4096);
        machine.loadProgram({
            make_imm(Opcode::MOVI, 1, 0, 40),
            make_imm(Opcode::MOVI, 2, 0, 2),
            make_r3(Opcode::ADD, 3, 1, 2),
            make_imm(Opcode::HALT, 0, 0, 0)
        }, 0x1000u);

        machine.run();
        assert(machine.cpu().readRegister(3) == 42u);
        assert(machine.cpu().halted());
    }

    {
        Machine machine(4096);
        machine.loadProgram({
            make_imm(Opcode::MOVI, 1, 0, 10),
            make_imm(Opcode::MOVI, 2, 0, 5),
            make_r3(Opcode::SUB, 3, 1, 2),
            make_imm(Opcode::HALT, 0, 0, 0)
        }, 0x1000u);

        machine.run();
        assert(machine.cpu().readRegister(3) == 5u);
    }

    {
        Machine machine(4096);
        machine.loadProgram({
            make_imm(Opcode::MOVI, 1, 0, 3),
            make_imm(Opcode::MOVI, 2, 0, 7),
            make_r3(Opcode::AND, 3, 1, 2),
            make_imm(Opcode::HALT, 0, 0, 0)
        }, 0x1000u);

        machine.run();
        assert(machine.cpu().readRegister(3) == 3u);
    }

    std::cout << "cpu tests passed\n";
    return 0;
}
