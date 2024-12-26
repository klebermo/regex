#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "transition.hpp"

class Automato {
private:
    SyntaxTree * syntaxTree;
    std::vector<Transition> transitions;
    int finalState;

    std::pair<int, int> buildTransitions(SyntaxNode * node, int stateCounter);
    std::unordered_set<int> epsilonClosure(const std::unordered_set<int>& states) const;
    void addTransition(int from, int to, char value);    
public:
    Automato(std::string regex);
    ~Automato();
    void buildTransitions();

    bool matches(std::string& input);
    std::pair<int, int> find(const std::string& input);
    std::vector<std::pair<int, int>> matchAll(const std::string& input);
    void replace(std::string& input, std::string replacement);
    bool isMatch(const std::string& input);    
};

#endif
