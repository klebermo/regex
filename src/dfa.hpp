#ifndef dfa_hpp
#define dfa_hpp

#include "nfa.hpp"

class DFA : public NFA {
public:
    DFA(NFA nfa);
    ~DFA();
};

#endif
