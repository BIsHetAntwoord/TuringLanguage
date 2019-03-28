#ifndef INTCODE_SYMBOL_HPP_INCLUDED
#define INTCODE_SYMBOL_HPP_INCLUDED

#include "intcode/datatype.hpp"

#include <memory>

class Symbol
{
    private:
        std::unique_ptr<DataType> type;
    public:
        Symbol(DataType*);
        ~Symbol() = default;

        inline DataType* getType() const
        {
            return this->type.get();
        }
};

#endif // INTCODE_SYMBOL_HPP_INCLUDED
