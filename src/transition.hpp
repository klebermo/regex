#ifndef transition_hpp
#define transition_hpp

#include "syntax_tree.hpp"

class State {
public:
    int id;

    State();
    State(int id);
};

class Transition {
public:
    State from;
    char symbol;
    State to;

    Transition();
    Transition(int from, int to, char symbol);
};

#endif
