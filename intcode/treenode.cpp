#include "intcode/treenode.hpp"
#include "error/exceptions.hpp"

template <typename T>
void resolve_rvalue(std::unique_ptr<T>& node)
{
    const DataType* current_type = node->getType();
    if(current_type->getBaseType() == BaseType::REFERENCE)
    {
        T* raw_ptr = node.get();
        node.release();
        node = std::make_unique<T>(new ReferenceAccessNode(raw_ptr));
    }
}

//Constructors
GlobalDeclListNode::GlobalDeclListNode(GlobalDeclNode* lop, GlobalDeclNode* rop) : lop(lop), rop(rop) {}

FunctionDeclNode::FunctionDeclNode(DataType* rettype, const std::string& name, ArgNode* args, StatementNode* content) : name(name), rettype(rettype), args(args), content(content) {}

ArgListNode::ArgListNode(ArgNode* prev_args, ArgNode* next_args) : prev_args(prev_args), next_args(next_args) {}

StatementListNode::StatementListNode(StatementNode* lop, StatementNode* rop) : lop(lop), rop(rop) {}

ExpressionStatementNode::ExpressionStatementNode(ExpressionNode* op) : op(op) {}

AssignNode::AssignNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

AddNode::AddNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

VariableNode::VariableNode(const std::string& name) : name(name) {}

IntegerNode::IntegerNode(uint32_t value) : value(value) {}

BoolNode::BoolNode(bool value) : value(value) {}

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
    this->args->semanticCheck(symb);
    this->content->semanticCheck(symb);
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
    this->type = std::make_unique(lop_type->copy());
}

void AddNode::semanticCheck(SymbolTable* symb)
{
    this->lop->semanticCheck(symb);
    this->rop->semanticCheck(symb);

    const DataType* lop_type = this->lop->getType();
    const DataType* rop_type = this->rop->getType();

    if(*lop_type != *rop_type)
        throw TypeCheckException("Invalid addition between ", *lop_type, " and ", *rop_type);

    this->type = std::make_unique(lop_type->copy());
}

