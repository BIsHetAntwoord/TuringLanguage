#include "intcode/treenode.hpp"
#include "error/exceptions.hpp"
#include "intcode/symtab.hpp"
#include "intcode/symbol.hpp"

template <typename T>
void resolve_rvalue(std::unique_ptr<T>& node)
{
    const DataType* current_type = node->getType();
    if(current_type->getBaseType() == BaseType::REFERENCE)
    {
        T* raw_ptr = node.get();
        node.release();
        node = std::unique_ptr<T>(new ReferenceAccessNode(raw_ptr));
    }
}

//Semantic checking
void GlobalDeclListNode::semanticCheck(SymbolTable* symb)
{
    this->lop->semanticCheck(symb);
    this->rop->semanticCheck(symb);
}

void EmptyDeclNode::semanticCheck(SymbolTable* symb)
{

}

void FunctionDeclNode::semanticCheck(SymbolTable* symb)
{
    //Functions should already be in the semantic table
    this->func_scope = std::unique_ptr<Scope>(symb->makeScope());

    this->args->semanticCheck(symb);
    this->content->semanticCheck(symb);

    symb->popScope();
}

void ArgListNode::semanticCheck(SymbolTable* symb)
{
    this->prev_args->semanticCheck(symb);
    this->next_args->semanticCheck(symb);
}

void EmptyArgNode::semanticCheck(SymbolTable* symb)
{

}

void EmptyNode::semanticCheck(SymbolTable* symb)
{

}

void StatementListNode::semanticCheck(SymbolTable* symb)
{
    this->lop->semanticCheck(symb);
    this->rop->semanticCheck(symb);
}

void ExpressionStatementNode::semanticCheck(SymbolTable* symb)
{
    this->op->semanticCheck(symb);
}

void AssignNode::semanticCheck(SymbolTable* symb)
{
    this->lop->semanticCheck(symb);
    this->rop->semanticCheck(symb);

    resolve_rvalue(this->rop);

    //Assert we can assign
    const DataType* lop_type = this->lop->getType();
    const DataType* rop_type = this->rop->getType();

    if(lop_type->getBaseType() != BaseType::REFERENCE)
        throw TypeCheckException("Assignment to non-lvalue type: ", *lop_type, " from ", *rop_type);

    const DataType* lop_subtype = lop_type->getSubType();
    if(*lop_subtype != *rop_type)
        throw TypeCheckException("Invalid conversion from ", *rop_type, " to ", *lop_subtype, " for assignment");

    //Generate the return type
    this->type = std::unique_ptr<DataType>(lop_type->copy());
}

void AddNode::semanticCheck(SymbolTable* symb)
{
    this->lop->semanticCheck(symb);
    this->rop->semanticCheck(symb);

    const DataType* lop_type = this->lop->getType();
    const DataType* rop_type = this->rop->getType();

    if(*lop_type != *rop_type)
        throw TypeCheckException("Invalid addition between ", *lop_type, " and ", *rop_type);
    if(!(lop_type->isArithmetic() || lop_type->isPointer()))
        throw TypeCheckException("Attempted to perform arithmetic on non-arithmetic type ", *lop_type);

    this->type = std::unique_ptr<DataType>(lop_type->copy());
}

void VariableNode::semanticCheck(SymbolTable* symb)
{
    this->symbol = symb->getSymbol(this->name);
    if(this->symbol == nullptr)
        throw SemanticException("Undeclared variable ", this->name);

    this->type = std::unique_ptr<DataType>(new DataType(BaseType::REFERENCE, this->symbol->getType()->copy()));
}

void DeclarationNode::semanticCheck(SymbolTable* symb)
{
    this->symbol = symb->declareSymbol(this->name, this->var_type.get());
    if(this->symbol == nullptr)
        throw SemanticException("Redeclaration of variable ", this->name);

    this->type = std::unique_ptr<DataType>(new DataType(BaseType::REFERENCE, this->symbol->getType()->copy()));
}

void IntegerNode::semanticCheck(SymbolTable* symb)
{
    this->type = std::make_unique<DataType>(BaseType::U32);
}

void BoolNode::semanticCheck(SymbolTable* symb)
{
    this->type = std::make_unique<DataType>(BaseType::BOOL);
}

void ReferenceAccessNode::semanticCheck(SymbolTable* symb)
{
    //Should not happen
}
