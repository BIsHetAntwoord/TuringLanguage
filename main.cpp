#include "parser/parser.hpp"
#include "intcode/treenode.hpp"
#include "intcode/symtab.hpp"
#include "error/exceptions.hpp"
#include "intcode/intinstr.hpp"
#include "intcode/intgenerate.hpp"
#include "intcode/declaration.hpp"
#include "turing/generator.hpp"

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

        GlobalDeclNode* node = parser.parse();
        if(node != nullptr)
        {
            SymbolTable symtab;
            std::cout << "Syntax tree:" << std::endl;
            node->semanticCheck(&symtab);
            node->print(std::cout);
            std::cout << std::endl;

            compile_info info;
            std::cout << "Bytecode declarations:" << std::endl;
            auto x = node->generateDecl(info);

            for(auto& decl : x)
            {
                std::cout << "Declaration: " << decl->getName() << std::endl;
                decl->getContent()->print(std::cout);
            }

            TuringGenerator gen(x);
            gen.generate();
        }
    }
    catch(CompilerException& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }


    return 0;
}
