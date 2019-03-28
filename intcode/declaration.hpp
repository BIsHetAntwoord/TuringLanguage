#ifndef INTCODE_DECLARATION_HPP_INCLUDED
#define INTCODE_DECLARATION_HPP_INCLUDED

#include <string>
#include <memory>

class DataType;
class IntInstr;

class Declaration
{
    private:
        std::string name;
        std::unique_ptr<DataType> type;
        std::unique_ptr<IntInstr> content;
    public:
        Declaration(const std::string&, DataType*, IntInstr*);
        ~Declaration() = default;
};

#endif // INTCODE_DECLARATION_HPP_INCLUDED
