#ifndef INTCODE_TREENODE_HPP_INCLUDED
#define INTCODE_TREENODE_HPP_INCLUDED

#include "intcode/datatype.hpp"

class ExpressionNode;

class TreeNode
{
    public:
        virtual ~TreeNode() = default;
};

class StatementNode : public TreeNode
{
    public:
        virtual ~StatementNode() = default;
};

class EmptyNode : public StatementNode
{
    public:
        virtual ~EmptyNode() = default;
};

class StatementListNode : public StatementNode
{
    private:
        std::unique_ptr<StatementNode> lop;
        std::unique_ptr<StatementNode> rop;
    public:
        StatementListNode(StatementNode*, StatementNode*);

        virtual ~StatementListNode();
};

class ExpressionStatementNode : public StatementNode
{
    public:
        ExpressionStatementNode(ExpressionNode*);

        virtual ~ExpressionStatementNode() = default;
};

class ExpressionNode : public TreeNode
{
    private:
        DataType type;
    public:
        virtual ~ExpressionNode() = default;

        virtual void calcTypes() = 0;
};

class AssignNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        AssignNode(ExpressionNode*, ExpressionNode*);

        virtual ~AssignNode() = default;

        virtual void calcTypes();
};

class AddNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        AddNode(ExpressionNode*, ExpressionNode*);

        virtual ~AddNode() = default;

        virtual void calcTypes();
};

class VariableNode : public ExpressionNode
{
    private:
        std::string name;
    public:
        VariableNode(const std::string&);
        virtual ~VariableNode() = default;

        virtual void calcTypes();
};

class IntegerNode : public ExpressionNode
{
    private:
        uint32_t value;
    public:
        IntegerNode(uint32_t);
        virtual ~IntegerNode() = default;

        virtual void calcTypes();
};

class BoolNode : public ExpressionNode
{
    private:
        bool value;
    public:
        BoolNode(bool);
        virtual ~BoolNode() = default;

        virtual void calcTypes();
};

#endif // INTCODE_TREENODE_HPP_INCLUDED
