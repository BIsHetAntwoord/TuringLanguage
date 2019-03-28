#ifndef TURING_GENERATOR_HPP_INCLUDED
#define TURING_GENERATOR_HPP_INCLUDED

#include <vector>
#include <memory>
#include <unordered_map>

#include "turing/state.hpp"

class Declaration;
class IntInstr;

class TuringGenerator
{
    private:
        std::vector<std::unique_ptr<Declaration>>& decls;
        std::unique_ptr<State> state_accept;
        std::unique_ptr<State> state_reject;

        std::vector<std::unique_ptr<State>> states;
        std::unordered_map<IntInstr*, State*> instr_state_lookup;
        std::unordered_map<Declaration*, State*> decl_state_lookup;
        std::unordered_map<Declaration*, State*> decl_epi_state_lookup;

        void generate(Declaration*);

        void genPrologue(Declaration*);
        void genEpilogue(Declaration*);

        State* getState(Declaration*);
        State* getState(IntInstr*);
        State* getEpiState(Declaration*);
    public:
        TuringGenerator(std::vector<std::unique_ptr<Declaration>>&);
        ~TuringGenerator() = default;

        void generate();
};

#endif // TURING_GENERATOR_HPP_INCLUDED
