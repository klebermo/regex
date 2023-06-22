#ifndef dfa_hpp
#define dfa_hpp

#include "automato.hpp"

class DFA : public Automato {
public:
    DFA(SyntaxTree& syntaxTree);
    ~DFA();
    void addTransition(int currentState, char symbol, int nextState);
    void setStartState(int state);
    void addAcceptState(int state);
    bool isAcceptedState(int state);
    int getStartState();
    std::vector<int> getNextState(int currentState, char symbol);
    void generateTransitions(SyntaxNode * node);
};

#endif
