#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "transition.hpp"

class Automato {
private:
    SyntaxTree * syntaxTree;
    std::vector<Transition> transitions;
    int finalState;

    std::pair<int, int> buildTransitions(SyntaxNode * node, int stateCounter);
    void addTransition(int from, int to, char value);    
public:
    Automato(std::string regex);
    ~Automato();

    void buildTransitions();
    void printTransitions();
    std::vector<Transition> getTransitions();
    int getFinalState();

    std::unordered_set<int> epsilonClosure(const std::unordered_set<int>& states) const;
};

#endif
