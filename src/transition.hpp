#include "syntax_tree.hpp"

#ifndef state_hpp
#define state_hpp

class State {
private:
    int id;
public:
    State();
    State(int id);

    int getId();
};

#endif

#ifndef transition_hpp
#define transition_hpp

class Transition {
private:
    State from;
    char symbol;
    State to;
public:
    Transition();
    Transition(int from, int to, char symbol);

    int _from();
    char _symbol();
    int _to();
};

#endif
