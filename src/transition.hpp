#ifndef transition_hpp
#define transition_hpp

#include "state.hpp"

class Transition {
public:
    State from;
    char symbol;
    State to;

    Transition(int from, int to, char symbol) : from(from), to(to), symbol(symbol) {}
    Transition(int from, int to, char symbol, bool isFinal) : from(from), to(to, isFinal), symbol(symbol) {}
};

#endif
