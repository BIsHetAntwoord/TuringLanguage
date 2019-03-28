#include "intcode/symtab.hpp"
#include "intcode/symbol.hpp"
#include "intcode/datatype.hpp"

Scope::Scope(Scope* parent) : parent_scope(parent) {}

Scope::~Scope() {}

Symbol* Scope::getSymbol(const std::string& symb) const
{
    if(this->symbols.count(symb) > 0)
        return this->symbols.at(symb);
    return nullptr;
}

Symbol* Scope::declareSymbol(const std::string& symb, DataType* type)
{
    if(this->getSymbol(symb) != nullptr)
        return nullptr;
    this->symbols[symb] = new Symbol(type->copy());
    return this->symbols[symb];
}

SymbolTable::SymbolTable()
{
    this->current_scope = new Scope(nullptr);
}

SymbolTable::~SymbolTable()
{
    delete this->current_scope;
}

Symbol* SymbolTable::getSymbol(const std::string& symb) const
{
    Scope* current_search = this->current_scope;

    while(current_search != nullptr)
    {
        Symbol* result = current_search->getSymbol(symb);
        if(result != nullptr)
            return result;
        current_search = current_search->getParent();
    }
    return nullptr;
}

Symbol* SymbolTable::declareSymbol(const std::string& symb, DataType* type)
{
    return this->current_scope->declareSymbol(symb, type);
}

Scope* SymbolTable::makeScope()
{
    Scope* new_scope = new Scope(this->current_scope);
    this->current_scope = new_scope;
    return this->current_scope;
}

void SymbolTable::popScope()
{
    this->current_scope = this->current_scope->getParent();
}
