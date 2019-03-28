#ifndef INTCODE_INTINSTR_HPP_INCLUDED
#define INTCODE_INTINSTR_HPP_INCLUDED

#include <cstddef>

enum class Opcode
{
    WRITE, //Type: size, operand: number of bytes to write
    POP, //Type: size, operand: number of bytes to pop

    ADD_U32, //Type: default
    ADD_PTR, //Type: size, operand: number of bytes in pointer subtype
};

class IntInstr
{
    private:
        Opcode op;
        IntInstr* next = nullptr;
    public:
        IntInstr(Opcode);
        virtual ~IntInstr();

        inline IntInstr* getNext() const
        {
            return this->next;
        }
        inline void setNext(IntInstr* next)
        {
            this->next = next;
        }
};

class SizeIntInstr : public IntInstr
{
    private:
        size_t val;
    public:
        SizeIntInstr(Opcode, size_t);
        virtual ~SizeIntInstr() = default;
};

#endif // INTCODE_INTINSTR_HPP_INCLUDED
