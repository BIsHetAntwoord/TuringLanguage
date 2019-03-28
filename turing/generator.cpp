#include "turing/generator.hpp"
#include "intcode/declaration.hpp"

TuringGenerator::TuringGenerator(std::vector<std::unique_ptr<Declaration>>& decls) : decls(decls),
                                                                state_accept(new State()),
                                                                state_reject(new State()) {}

void TuringGenerator::generate()
{
    for(auto& decl : this->decls)
    {
        this->generate(decl.get());
    }
}

void TuringGenerator::generate(Declaration* decl)
{
    this->genPrologue(decl);

    this->genEpilogue(decl);
}

void TuringGenerator::genPrologue(Declaration* decl)
{
    //TODO: create some form of prologue
    State* state = this->getState(decl);

    //Finish by transitioning to the start of the function body
    State* instr_state = this->getState(decl->getContent());
    state->addAllTransitions(instr_state, StackTransition::STAY);
}

void TuringGenerator::genEpilogue(Declaration* decl)
{
    //TODO: create some form of epilogue
    State* state = this->getEpiState(decl);

    //Transition to accept for now
    state->addAllTransitions(this->state_accept.get(), StackTransition::STAY);
}

State* TuringGenerator::getState(Declaration* decl)
{
    if(this->decl_state_lookup.count(decl) > 0)
        return this->decl_state_lookup[decl];
    this->decl_state_lookup[decl] = new State();
    return this->decl_state_lookup[decl];
}

State* TuringGenerator::getState(IntInstr* instr)
{
    if(this->instr_state_lookup.count(instr) > 0)
        return this->instr_state_lookup[instr];
    this->instr_state_lookup[instr] = new State();
    return this->instr_state_lookup[instr];
}

State* TuringGenerator::getEpiState(Declaration* decl)
{
    if(this->decl_epi_state_lookup.count(decl) > 0)
        this->decl_epi_state_lookup[decl];
    this->decl_epi_state_lookup[decl] = new State();
    return this->decl_epi_state_lookup[decl];
}
