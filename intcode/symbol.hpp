#ifndef INTCODE_SYMBOL_HPP_INCLUDED
#define INTCODE_SYMBOL_HPP_INCLUDED

#include "intcode/datatype.hpp"

#include <memory>
#include <string>

class Symbol
{
    private:
        std::unique_ptr<DataType> type;
        std::string name;
    public:
        Symbol(DataType*, const std::string&);
        ~Symbol() = default;

        inline DataType* getType() const
        {
            return this->type.get();
        }

        inline std::string getName() const
        {
            return this->name;
        }
};

#endif // INTCODE_SYMBOL_HPP_INCLUDED
