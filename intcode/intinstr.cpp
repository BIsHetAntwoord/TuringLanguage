#include "intcode/intinstr.hpp"
#include "intcode/symbol.hpp"

#include <iostream>

const char* OPCODE_NAMES[] = {
    "READ",
    "WRITE",
    "POP",
    "SYMB_ADDR",

    "ADD_U32",
    "ADD_PTR",

    "PUSH_U32",
    "PUSH_BOOL"
};

const char* opcode_get_name(Opcode op)
{
    return OPCODE_NAMES[(size_t)op];
}

IntInstr::IntInstr(Opcode op) : op(op) {}

IntInstr::~IntInstr()
{
    delete this->next;
}

void IntInstr::print(std::ostream& os) const
{
    os << OPCODE_NAMES[(size_t)this->op] << std::endl;

    if(this->next != nullptr)
        this->next->print(os);
}

SizeIntInstr::SizeIntInstr(Opcode op, size_t val) : IntInstr(op), val(val) {}

void SizeIntInstr::print(std::ostream& os) const
{
    os << OPCODE_NAMES[(size_t)this->op] << " " << this->val << std::endl;

    if(this->next != nullptr)
        this->next->print(os);
}

SymbolIntInstr::SymbolIntInstr(Opcode op, Symbol* symb) : IntInstr(op), symb(symb) {}

void SymbolIntInstr::print(std::ostream& os) const
{
    os << OPCODE_NAMES[(size_t)this->op] << " " << this->symb->getName() << " -> " << *this->symb->getType() << std::endl;

    if(this->next != nullptr)
        this->next->print(os);
}
