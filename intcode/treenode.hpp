#ifndef INTCODE_TREENODE_HPP_INCLUDED
#define INTCODE_TREENODE_HPP_INCLUDED

#include "intcode/datatype.hpp"

class StatementNode;
class ArgNode;
class ExpressionNode;
class SymbolTable;

class TreeNode
{
    public:
        virtual ~TreeNode() = default;

        virtual void semanticCheck(SymbolTable*) = 0;
};

class GlobalDeclNode : public TreeNode
{
    public:
        virtual ~GlobalDeclNode() = default;
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
};

class EmptyDeclNode : public GlobalDeclNode
{
    public:
        EmptyDeclNode() = default;
        virtual ~EmptyDeclNode() = default;

        virtual void semanticCheck(SymbolTable*);
};

class FunctionDeclNode : public GlobalDeclNode
{
    private:
        std::string name;
        std::unique_ptr<DataType> rettype;
        std::unique_ptr<ArgNode> args;
        std::unique_ptr<StatementNode> content;
    public:
        FunctionDeclNode(DataType*, const std::string&, ArgNode*, StatementNode*);
        virtual ~FunctionDeclNode() = default;

        virtual void semanticCheck(SymbolTable*);
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
};

class EmptyArgNode : public ArgNode
{
    public:
        EmptyArgNode() = default;
        virtual ~EmptyArgNode() = default;

        virtual void semanticCheck(SymbolTable*);
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
};

class StatementListNode : public StatementNode
{
    private:
        std::unique_ptr<StatementNode> lop;
        std::unique_ptr<StatementNode> rop;
    public:
        StatementListNode(StatementNode*, StatementNode*);

        virtual ~StatementListNode();

        virtual void semanticCheck(SymbolTable*);
};

class ExpressionStatementNode : public StatementNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        ExpressionStatementNode(ExpressionNode*);

        virtual ~ExpressionStatementNode() = default;

        virtual void semanticCheck(SymbolTable*);
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
};

class VariableNode : public ExpressionNode
{
    private:
        std::string name;
    public:
        VariableNode(const std::string&);
        virtual ~VariableNode() = default;

        virtual void semanticCheck(SymbolTable*);
};

class IntegerNode : public ExpressionNode
{
    private:
        uint32_t value;
    public:
        IntegerNode(uint32_t);
        virtual ~IntegerNode() = default;

        virtual void semanticCheck(SymbolTable*);
};

class BoolNode : public ExpressionNode
{
    private:
        bool value;
    public:
        BoolNode(bool);
        virtual ~BoolNode() = default;

        virtual void semanticCheck(SymbolTable*);
};

class ReferenceAccessNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        ReferenceAccessNode(ExpressionNode*); //Required operand to be semantic checked
        virtual ~ReferenceAccessNode() = default;

        virtual void semanticCheck(SymbolTable*);
};

#endif // INTCODE_TREENODE_HPP_INCLUDED
