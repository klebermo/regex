#ifndef transition_hpp
#define transition_hpp

#include "syntax_tree.hpp"

class State {
private:
    int id;
public:
    State();
    State(int id);

    int getId();
    void setId(int id);
};

class Transition {
private:
    State from;
    char symbol;
    State to;
public:
    Transition();
    Transition(int from, int to, char symbol);
};

#endif
