#ifndef INTCODE_INTINSTR_HPP_INCLUDED
#define INTCODE_INTINSTR_HPP_INCLUDED

#include <cstddef>
#include <iosfwd>

class Symbol;

enum class Opcode
{
    READ, //Type: size, operand: number of bytes to read
    WRITE, //Type: size, operand: number of bytes to write
    POP, //Type: size, operand: number of bytes to pop
    SYMB_ADDR, //Type: symbol, operand: symbol to load address of

    ADD_U32, //Type: default
    ADD_PTR, //Type: size, operand: number of bytes in pointer subtype

    PUSH_U32, //Type: u32, operand: constant
    PUSH_BOOL, //Type: bool, operand: constant
};

class IntInstr
{
    protected:
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

        virtual void print(std::ostream&) const;
};

class SizeIntInstr : public IntInstr
{
    private:
        size_t val;
    public:
        SizeIntInstr(Opcode, size_t);
        virtual ~SizeIntInstr() = default;

        virtual void print(std::ostream&) const;
};

class SymbolIntInstr : public IntInstr
{
    private:
        Symbol* symb;
    public:
        SymbolIntInstr(Opcode, Symbol*);
        virtual ~SymbolIntInstr() = default;

        virtual void print(std::ostream&) const;
};

template <typename T>
class OperandIntInstr : public IntInstr
{
    private:
        T value;
    public:
        OperandIntInstr(Opcode, const T&);
        virtual ~OperandIntInstr() = default;

        virtual void print(std::ostream&) const;
};

#include "intcode/intinstr.inl"

#endif // INTCODE_INTINSTR_HPP_INCLUDED
