#ifndef INTCODE_SYMTAB_HPP_INCLUDED
#define INTCODE_SYMTAB_HPP_INCLUDED

#include <unordered_map>

class DataType;
class Symbol;

class Scope
{
    private:
        Scope* parent_scope;
        std::unordered_map<std::string, Symbol*> symbols;
    public:
        Scope(Scope*);
        ~Scope();

        Symbol* getSymbol(const std::string&) const;
        Symbol* declareSymbol(const std::string&, DataType*);

        inline Scope* getParent() const
        {
            return this->parent_scope;
        }
};

class SymbolTable
{
    private:
        Scope* current_scope;
    public:
        SymbolTable();
        ~SymbolTable();

        Symbol* getSymbol(const std::string&) const;
        Symbol* declareSymbol(const std::string&, DataType*);

        Scope* makeScope();
        void popScope();
};

#endif // INTCODE_SYMTAB_HPP_INCLUDED
