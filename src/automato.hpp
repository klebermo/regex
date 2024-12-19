#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "syntax_tree.hpp"

class Automato {
protected:
    SyntaxTree * syntaxTree;

    std::set<int> startStates;
    std::set<char> alphabet;
    std::map<std::pair<int, char>, std::set<int>> transitions;
    std::set<int> endStates;
public:
    virtual Automato * build(std::string regex) = 0;

    Automato();
    virtual ~Automato();

    virtual void addTransition(int from, int to, char symbol) = 0;
    virtual void setStartState(int state) = 0;
    virtual void setEndState(int state) = 0;

    virtual std::set<int> getStartStates() const = 0;
    virtual std::set<char> getAlphabet() const = 0;
    virtual std::map<std::pair<int, char>, std::set<int>> getTransitions() const = 0;
    virtual std::set<int> getEndStates() const = 0;

    virtual std::vector<int> getNextState(int state, char symbol) const = 0;
};

#endif
