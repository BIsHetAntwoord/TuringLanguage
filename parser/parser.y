%{
#include "parser/parser_info.hpp"
#include "intcode/treenode.hpp"

#include <iostream>

#define scanner x->scanner
%}

%lex-param {void* scanner}
%parse-param {parse_info* x}
%pure-parser
%error-verbose

%define api.prefix {parser_yy}

%token KEYW_BOOL "bool"
%token KEYW_FALSE "false"
%token KEYW_TRUE "true"
%token KEYW_U32 "u32"
%token KEYW_VOID "void"

%token SEMICOLON ";"
%token ASSIGN "="
%token PLUS "+"
%token MIN "-"
%token MUL "*"
%token DIV "/"
%token MOD "%"
%token BITAND "&"
%token BITOR "|"
%token BITXOR "^"
%token BITNOT "~"
%token CONCAT ".."

%token OPEN_PAR "("
%token CLOSE_PAR ")"
%token OPEN_CB "{"
%token CLOSE_CB "}"

%token<integer> INTEGER "integer"
%token<str> ID "identifier"
%token<str> STRING "string"
%token ERROR_TOKEN "error token"

%destructor {delete[] $$;} <str>
%destructor {delete $$;} <node> <type>

%right ASSIGN
%left CONCAT
%left BITXOR
%left BITOR
%left BITAND
%left PLUS MIN
%left MUL DIV MOD
%right UPLUS UMIN BITNOT TRY

%type<node> statement_list statement expression calc_expression constant
%type<node> global_decl_list function arg_list
%type<node> lvalue rvalue
%type<type> rettype datatype

%%

root
    : global_decl_list                                                  {x->root = $1;}
    ;

global_decl_list
    : global_decl_list function                                         {$$ = new GlobalDeclListNode((GlobalDeclNode*)$1, (GlobalDeclNode*)$2);}
    |                                                                   {$$ = new EmptyDeclNode();}
    ;

function
    : rettype ID OPEN_PAR arg_list CLOSE_PAR
          OPEN_CB statement_list CLOSE_CB                               {$$ = new FunctionDeclNode($1, $2, (ArgNode*)$4, (StatementNode*)$7); delete[] $2;}
    ;

arg_list
    :                                                                   {$$ = new EmptyArgNode();}
    ;

statement_list
    : statement_list statement                                          {$$ = new StatementListNode((StatementNode*)$1, (StatementNode*)$2);}
    |                                                                   {$$ = new EmptyNode();}
    ;

statement
    : SEMICOLON                                                         {$$ = new EmptyNode();}
    | expression SEMICOLON                                              {$$ = new ExpressionStatementNode((ExpressionNode*)$1);}
    ;

expression
    : lvalue                                                            {$$ = $1;}
    | calc_expression                                                   {$$ = $1;}
    ;

calc_expression
    : rvalue                                                            {$$ = $1;}
    | expression ASSIGN expression                                      {$$ = new AssignNode((ExpressionNode*)$1, (ExpressionNode*)$3);}
    | expression PLUS expression                                        {$$ = new AddNode((ExpressionNode*)$1, (ExpressionNode*)$3);}
    | OPEN_PAR calc_expression CLOSE_PAR                                {$$ = $2;}
    ;

lvalue
    : ID                                                                {$$ = new VariableNode($1); delete[] $1;}
    | OPEN_PAR lvalue CLOSE_PAR                                         {$$ = $2;}
    | datatype ID                                                       {$$ = new DeclarationNode($1, $2); delete[] $2;}
    ;

rvalue
    : constant                                                          {$$ = $1;}
    ;

constant
    : INTEGER                                                           {$$ = new IntegerNode($1);}
    | KEYW_TRUE                                                         {$$ = new BoolNode(true);}
    | KEYW_FALSE                                                        {$$ = new BoolNode(false);}
    ;

datatype
    : KEYW_U32                                                          {$$ = new DataType(BaseType::U32);}
    | KEYW_BOOL                                                         {$$ = new DataType(BaseType::BOOL);}
    ;

rettype
    : datatype                                                          {$$ = $1;}
    | KEYW_VOID                                                         {$$ = new DataType(BaseType::VOID);}
    ;

%%

void parser_yyerror(parse_info* x, const char* msg)
{
    std::cerr << "Error at line " << x->line << ": " << msg << std::endl;
    ++x->errors;
}
