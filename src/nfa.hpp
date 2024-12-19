#ifndef nfa_hpp
#define nfa_hpp

#include "automato.hpp"

class NFA : public Automato {
public:
    NFA();
    ~NFA();

    NFA * build(std::string regex) override;
    NFA * build(SyntaxNode * node);

    void addTransition(int from, int to, char symbol) override;
    void setStartState(int state) override;
    void setEndState(int state) override;

    std::set<int> getStartStates() const override;
    std::set<char> getAlphabet() const override;
    std::map<std::pair<int, char>, std::set<int>> getTransitions() const override;
    std::set<int> getEndStates() const override;

    std::vector<int> getNextState(int state, char symbol) const override;

    NFA * emptyNFA();
    NFA * unionNFA(NFA * nfa1, NFA * nfa2);
    NFA * concatenateNFA(NFA * nfa1, NFA * nfa2);
    NFA * kleeneStar(NFA * nfa);
    NFA * anchorStart();
    NFA * anchorEnd();
    NFA * fromLiteral(char symbol);
};

#endif
