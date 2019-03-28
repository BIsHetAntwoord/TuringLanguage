#ifndef INTCODE_TREENODE_HPP_INCLUDED
#define INTCODE_TREENODE_HPP_INCLUDED

#include "intcode/datatype.hpp"

#include <iosfwd>
#include <vector>

class StatementNode;
class ArgNode;
class ExpressionNode;
class SymbolTable;
class Symbol;
class Scope;
struct compile_info;
class IntInstr;
class Declaration;

class TreeNode
{
    public:
        virtual ~TreeNode() = default;

        virtual void semanticCheck(SymbolTable*) = 0;
        virtual void print(std::ostream&, size_t = 0) const = 0;
        virtual IntInstr* generate(compile_info&) const = 0;
};

class GlobalDeclNode : public TreeNode
{
    public:
        virtual ~GlobalDeclNode() = default;

        virtual std::vector<std::unique_ptr<Declaration>> generateDecl(compile_info&) const = 0;
};

class GlobalDeclListNode : public GlobalDeclNode
{
    private:
        std::unique_ptr<GlobalDeclNode> lop;
        std::unique_ptr<GlobalDeclNode> rop;
    public:
        GlobalDeclListNode(GlobalDeclNode*, GlobalDeclNode*);
        virtual ~GlobalDeclListNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
        virtual std::vector<std::unique_ptr<Declaration>> generateDecl(compile_info&) const;
};

class EmptyDeclNode : public GlobalDeclNode
{
    public:
        EmptyDeclNode() = default;
        virtual ~EmptyDeclNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
        virtual std::vector<std::unique_ptr<Declaration>> generateDecl(compile_info&) const;
};

class FunctionDeclNode : public GlobalDeclNode
{
    private:
        std::string name;
        std::unique_ptr<DataType> rettype;
        std::unique_ptr<ArgNode> args;
        std::unique_ptr<StatementNode> content;
        std::unique_ptr<Scope> func_scope;
    public:
        FunctionDeclNode(DataType*, const std::string&, ArgNode*, StatementNode*);
        virtual ~FunctionDeclNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
        virtual std::vector<std::unique_ptr<Declaration>> generateDecl(compile_info&) const;
};

class ArgNode : public TreeNode
{
    public:
        virtual ~ArgNode() = default;
};

class ArgListNode : public ArgNode
{
    private:
        std::unique_ptr<ArgNode> prev_args;
        std::unique_ptr<ArgNode> next_args;
    public:
        ArgListNode(ArgNode*, ArgNode*);
        virtual ~ArgListNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class EmptyArgNode : public ArgNode
{
    public:
        EmptyArgNode() = default;
        virtual ~EmptyArgNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class StatementNode : public TreeNode
{
    public:
        virtual ~StatementNode() = default;
};

class EmptyNode : public StatementNode
{
    public:
        EmptyNode() = default;
        virtual ~EmptyNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class StatementListNode : public StatementNode
{
    private:
        std::unique_ptr<StatementNode> lop;
        std::unique_ptr<StatementNode> rop;
    public:
        StatementListNode(StatementNode*, StatementNode*);

        virtual ~StatementListNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class ExpressionStatementNode : public StatementNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        ExpressionStatementNode(ExpressionNode*);

        virtual ~ExpressionStatementNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class ExpressionNode : public TreeNode
{
    protected:
        std::unique_ptr<DataType> type;
    public:
        virtual ~ExpressionNode() = default;

        inline DataType* getType()
        {
            return this->type.get();
        }

        inline const DataType* getType() const
        {
            return this->type.get();
        }
};

class AssignNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        AssignNode(ExpressionNode*, ExpressionNode*);

        virtual ~AssignNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class AddNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        AddNode(ExpressionNode*, ExpressionNode*);

        virtual ~AddNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class VariableNode : public ExpressionNode
{
    private:
        std::string name;
        Symbol* symbol = nullptr;
    public:
        VariableNode(const std::string&);
        virtual ~VariableNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class DeclarationNode : public ExpressionNode
{
    private:
        std::string name;
        std::unique_ptr<DataType> var_type;
        Symbol* symbol = nullptr;
    public:
        DeclarationNode(DataType*, const std::string&);
        virtual ~DeclarationNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class IntegerNode : public ExpressionNode
{
    private:
        uint32_t value;
    public:
        IntegerNode(uint32_t);
        virtual ~IntegerNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class BoolNode : public ExpressionNode
{
    private:
        bool value;
    public:
        BoolNode(bool);
        virtual ~BoolNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

class ReferenceAccessNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        ReferenceAccessNode(ExpressionNode*); //Required operand to be semantic checked
        virtual ~ReferenceAccessNode() = default;

        virtual void semanticCheck(SymbolTable*);
        virtual void print(std::ostream&, size_t) const;
        virtual IntInstr* generate(compile_info&) const;
};

#endif // INTCODE_TREENODE_HPP_INCLUDED
