#ifndef nfa_hpp
#define nfa_hpp

#include "automato.hpp"

class NFA : public Automato {
private:
    std::unordered_map<std::pair<int, char>, std::unordered_set<int>, pair_hash> transitions;
    int startState;
    std::unordered_set<int> acceptStates;
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
