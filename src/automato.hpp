#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "syntax_tree.hpp"

#include <unordered_map>
#include <unordered_set>

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};
typedef struct pair_hash pair_hash;

class Automato {
protected:
    std::unordered_map<std::pair<int, char>, int, pair_hash> transitions;
    int startState;
    std::unordered_set<int> acceptStates;
public:
    virtual ~Automato() {};
    virtual void addTransition(int currentState, char symbol, int nextState) = 0;
    virtual void setStartState(int state) = 0;
    virtual void addAcceptState(int state) = 0;
    virtual bool isAcceptedState(int state) = 0;
    virtual int getStartState() = 0;
    virtual std::vector<int> getNextState(int currentState, char symbol) = 0;
    virtual void generateTransitions(SyntaxNode * node) = 0;
};

#endif
