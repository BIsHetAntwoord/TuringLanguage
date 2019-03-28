#ifndef PARSER_HPP_INCLUDED
#define PARSER_HPP_INCLUDED

#include <string>
#include <cstdio>

class GlobalDeclNode;

class Parser
{
    private:
        FILE* input;
    public:
        Parser(const std::string&);
        Parser(FILE*);
        ~Parser();

        GlobalDeclNode* parse();
};

#endif // PARSER_HPP_INCLUDED
