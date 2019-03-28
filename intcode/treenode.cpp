#include "intcode/treenode.hpp"
#include "intcode/symtab.hpp"

#include <iostream>

//Constructors
GlobalDeclListNode::GlobalDeclListNode(GlobalDeclNode* lop, GlobalDeclNode* rop) : lop(lop), rop(rop) {}

FunctionDeclNode::FunctionDeclNode(DataType* rettype, const std::string& name, ArgNode* args, StatementNode* content) : name(name), rettype(rettype), args(args), content(content) {}

ArgListNode::ArgListNode(ArgNode* prev_args, ArgNode* next_args) : prev_args(prev_args), next_args(next_args) {}

StatementListNode::StatementListNode(StatementNode* lop, StatementNode* rop) : lop(lop), rop(rop) {}

ExpressionStatementNode::ExpressionStatementNode(ExpressionNode* op) : op(op) {}

AssignNode::AssignNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

AddNode::AddNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

VariableNode::VariableNode(const std::string& name) : name(name) {}

DeclarationNode::DeclarationNode(DataType* type, const std::string& name) : name(name), var_type(type) {}

IntegerNode::IntegerNode(uint32_t value) : value(value) {}

BoolNode::BoolNode(bool value) : value(value) {}

ReferenceAccessNode::ReferenceAccessNode(ExpressionNode* op) : op(op)
{
    this->type = std::unique_ptr<DataType>(op->getType()->getSubType()->copy());
}

//Print
void print_indent(std::ostream& os, size_t level)
{
    for(size_t i = 0; i < level; ++i)
        os << "    ";
}

void GlobalDeclListNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);

    os << "global declaration:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

void EmptyDeclNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "empty declaration" << std::endl;
}

void FunctionDeclNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "function declaration (" << this->name << " -> " << *this->rettype << "):" << std::endl;
    this->args->print(os, level+1);
    this->content->print(os, level+1);
}

void ArgListNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "argument list:"<< std::endl;
    this->prev_args->print(os, level+1);
    this->next_args->print(os, level+1);
}

void EmptyArgNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "empty argument" << std::endl;
}

void EmptyNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "empty statement" << std::endl;
}

void StatementListNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "statement list:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

void ExpressionStatementNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "expression statement:" << std::endl;
    this->op->print(os, level+1);
}

void AssignNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "assignment -> " << *this->type << ":" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

void AddNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "addition -> " << *this->type << ":" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

void VariableNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "variable (" << this->name << ") -> " << *this->type << std::endl;
}

void DeclarationNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "variable declaration (" << this->name << " -> " << *this->var_type << ") -> " << *this->type << std::endl;
}

void IntegerNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "integer constant (" << this->value << ") -> " << *this->type << std::endl;
}

void BoolNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "boolean constant (" << (this->value ? "true" : "false") << ") -> " << *this->type << std::endl;
}

void ReferenceAccessNode::print(std::ostream& os, size_t level) const
{
    print_indent(os, level);
    os << "reference access -> " << *this->type << ":" << std::endl;
    this->op->print(os, level+1);
}
