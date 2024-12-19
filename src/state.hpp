#ifndef state_hpp
#define state_hpp

#include "syntax_tree.hpp"

class State {
public:
    int id;
    bool isFinal;

    State(int id) : id(id), isFinal(false) {}
    State(int id, bool isFinal) : id(id), isFinal(isFinal) {}
};

#endif
