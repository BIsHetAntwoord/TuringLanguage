#ifndef TURING_STATE_HPP_INCLUDED
#define TURING_STATE_HPP_INCLUDED

const size_t ALPHABET_MAX = 255;

class State;

enum class StackTransition
{
    STAY,
    LEFT,
    RIGHT
};

class Transition
{
    private:
        State* target;
        size_t byte;
        StackTransition transition;
};

class State
{
    private:
        Transition* transitions;
    public:
        State();
        ~State();

        void addAllTransitions(State*, StackTransition);
};

#endif // TURING_STATE_HPP_INCLUDED
