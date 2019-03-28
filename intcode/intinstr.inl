#include <iostream>

const char* opcode_get_name(Opcode);

template <typename T>
OperandIntInstr<T>::OperandIntInstr(Opcode op, const T& value) : IntInstr(op), value(value) {}

template <typename T>
void OperandIntInstr<T>::print(std::ostream& os) const
{
    os << opcode_get_name(this->op) << " " << this->value << std::endl;

    if(this->next != nullptr)
        this->next->print(os);
}
