#include "nfa.hpp"

NFA::NFA(SyntaxTree& syntaxTree) {
    this->startState = 0;
    this->generateTransitions(syntaxTree.getRoot());
}

NFA::~NFA() {
    //delete transitions;
}

void NFA::addTransition(int currentState, char symbol, int nextState) {
    transitions[std::make_pair(currentState, symbol)] = nextState;
}

void NFA::setStartState(int state) {
    startState = state;
}

void NFA::addAcceptState(int state) {
    acceptStates.insert(state);
}

bool NFA::isAcceptedState(int state) {
    return acceptStates.count(state) > 0;
}

int NFA::getStartState() {
    return startState;
}

std::vector<int> NFA::getNextState(int currentState, char symbol) {
    std::vector<int> nextStates;
    auto transition = std::make_pair(currentState, symbol);

    if(transitions.count(transition) > 0) {
        /*for(int nextState : transitions[transition]) {
            nextStates.push_back(nextState);
        }*/
        for(auto nextState : transitions) {
            nextStates.push_back(nextState.second);
        }
    }

    return nextStates;
}

void NFA::generateTransitions(SyntaxNode * node) {
    if(node == nullptr) {
        return;
    }

    char value = node->getValue();
    //int currentState = getNextState(startState, value)[0];
    //int nextState = getNextState(currentState, value)[0];

    if(node->isOperator()) {
        switch(value) {
            case '^':
                break;
            case '.':
                break;
            case '[':
                break;
            case ']':
                break;
            case '$':
                break;
            case '(':
                break;
            case ')':
                break;
            case '\n':
                break;
            case '*':
                break;
            case '{':
                break;
            case '}':
                break;
            case '?':
                break;
            case '+':
                break;
            case '|':
                break;            
        }
    } else {
        //
    }

    generateTransitions(node->getLeft());
    generateTransitions(node->getRight());
}