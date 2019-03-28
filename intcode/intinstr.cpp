#include "intcode/intinstr.hpp"

IntInstr::IntInstr(Opcode op) : op(op) {}

IntInstr::~IntInstr()
{
    delete this->next;
}

SizeIntInstr::SizeIntInstr(Opcode op, size_t val) : IntInstr(op), val(val) {}
