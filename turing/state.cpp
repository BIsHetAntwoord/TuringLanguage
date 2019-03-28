#include "turing/state.hpp"

State::State()
{
    this->transitions = new Transition[ALPHABET_MAX + 1];
}

State::~State()
{
    delete[] this->transitions;
}

void State::addAllTransitions(State* target, StackTransition trans)
{
    for(size_t i = 0; i <= ALPHABET_MAX; ++i)
    {
        Transition* transition = new Transition(target, i, trans);
        this->setTransition(i, transition);
    }
}
