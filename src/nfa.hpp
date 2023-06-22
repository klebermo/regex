#ifndef nfa_hpp
#define nfa_hpp

#include "automato.hpp"

class NFA : public Automato {
public:
    NFA(SyntaxTree& syntaxTree);
    ~NFA();
    void addTransition(int currentState, char symbol, int nextState);
    void setStartState(int state);
    void addAcceptState(int state);
    bool isAcceptedState(int state);
    int getStartState();
    std::vector<int> getNextState(int currentState, char symbol);
    void generateTransitions(SyntaxNode * node);
};

#endif
