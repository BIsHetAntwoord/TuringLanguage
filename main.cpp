#include "parser/parser.hpp"
#include "intcode/treenode.hpp"
#include "intcode/symtab.hpp"
#include "error/exceptions.hpp"
#include "intcode/intinstr.hpp"
#include "intcode/intgenerate.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cerr << "Not enough arguments given" << std::endl;
        return 1;
    }

    try
    {
        Parser parser(argv[1]);

        TreeNode* node = parser.parse();
        if(node != nullptr)
        {
            SymbolTable symtab;
            node->semanticCheck(&symtab);
            node->print(std::cout);

            compile_info info;
            node->generate(info);
        }
    }
    catch(CompilerException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }


    return 0;
}
