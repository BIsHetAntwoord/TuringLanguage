#include "intcode/intgenerate.hpp"
#include "intcode/treenode.hpp"
#include "intcode/intinstr.hpp"
#include "intcode/declaration.hpp"
#include "utils/constructs.hpp"

#include <algorithm>

IntInstr* concat(IntInstr* arg)
{
    return arg;
}

template <typename... Args>
IntInstr* concat(IntInstr* arg, Args... args)
{
    if(arg == nullptr)
        return concat(args...);

    IntInstr* current = arg;

    while(current->getNext() != nullptr)
        current = current->getNext();
    current->setNext(concat(args...));

    return arg;
}

//Global declaration generators
std::vector<std::unique_ptr<Declaration>> GlobalDeclListNode::generateDecl(compile_info& info) const
{
    auto lop_values = this->lop->generateDecl(info);
    auto rop_values = this->rop->generateDecl(info);

    lop_values.insert(lop_values.end(), std::make_move_iterator(rop_values.begin()), std::make_move_iterator(rop_values.end()));
    return lop_values;
}

std::vector<std::unique_ptr<Declaration>> EmptyDeclNode::generateDecl(compile_info& info) const
{
    return {};
}

std::vector<std::unique_ptr<Declaration>> FunctionDeclNode::generateDecl(compile_info& info) const
{
    std::vector<std::unique_ptr<Declaration>> retval;
    retval.emplace_back(new Declaration(this->name, this->rettype->copy(), this->content->generate(info)));
    return retval;
}

//Bytecode generators
IntInstr* GlobalDeclListNode::generate(compile_info& info) const
{
    return nullptr;
}

IntInstr* EmptyDeclNode::generate(compile_info& info) const
{
    return nullptr;
}

IntInstr* FunctionDeclNode::generate(compile_info& info) const
{
    return nullptr;
}

IntInstr* ArgListNode::generate(compile_info& info) const
{
    return nullptr;
}

IntInstr* EmptyArgNode::generate(compile_info& info) const
{
    return nullptr;
}

IntInstr* EmptyNode::generate(compile_info& info) const
{
    return nullptr;
}

IntInstr* StatementListNode::generate(compile_info& info) const
{
    std::unique_ptr<IntInstr> lop_code(this->lop->generate(info));
    std::unique_ptr<IntInstr> rop_code(this->rop->generate(info));

    return concat(lop_code.release(), rop_code.release());
}

IntInstr* ExpressionStatementNode::generate(compile_info& info) const
{
    std::unique_ptr<IntInstr> op_code(this->op->generate(info));
    std::unique_ptr<IntInstr> pop(new SizeIntInstr(Opcode::POP, this->op->getType()->size()));

    return concat(op_code.release(), pop.release());
}

IntInstr* AssignNode::generate(compile_info& info) const
{
    std::unique_ptr<IntInstr> lop_code(this->lop->generate(info));
    std::unique_ptr<IntInstr> rop_code(this->rop->generate(info));
    std::unique_ptr<IntInstr> write(new SizeIntInstr(Opcode::WRITE, this->rop->getType()->size()));
    std::unique_ptr<IntInstr> pop(new SizeIntInstr(Opcode::POP, this->rop->getType()->size()));

    return concat(lop_code.release(), rop_code.release(), write.release(), pop.release());
}

IntInstr* AddNode::generate(compile_info& info) const
{
    std::unique_ptr<IntInstr> lop_code(this->lop->generate(info));
    std::unique_ptr<IntInstr> rop_code(this->rop->generate(info));

    std::unique_ptr<IntInstr> operation([&]() -> IntInstr* {
        switch(this->lop->getType()->getBaseType()) {
            case BaseType::U32:
                return new IntInstr(Opcode::ADD_U32);
            case BaseType::POINTER:
                return new SizeIntInstr(Opcode::ADD_PTR, this->lop->getType()->getSubType()->size());
            default:
                return nullptr;
        }
    }());

    return concat(lop_code.release(), rop_code.release(), operation.release());
}

IntInstr* VariableNode::generate(compile_info& info) const
{
    return new SymbolIntInstr(Opcode::SYMB_ADDR, this->symbol);
}

IntInstr* DeclarationNode::generate(compile_info& info) const
{
    return new SymbolIntInstr(Opcode::SYMB_ADDR, this->symbol);
}

IntInstr* IntegerNode::generate(compile_info& info) const
{
    return new OperandIntInstr<uint32_t>(Opcode::PUSH_U32, this->value);
}

IntInstr* BoolNode::generate(compile_info& info) const
{
    return new OperandIntInstr<bool>(Opcode::PUSH_BOOL, this->value);
}

IntInstr* ReferenceAccessNode::generate(compile_info& info) const
{
    std::unique_ptr<IntInstr> op_code(this->op->generate(info));
    return concat(new SizeIntInstr(Opcode::READ, this->getType()->size()), op_code.release());
}
