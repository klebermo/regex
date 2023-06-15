#include "dfa.hpp"

DFA::DFA(SyntaxTree& syntaxTree) {
    this->startState = 0;
    this->generateTransitions(syntaxTree.getRoot());
}

DFA::~DFA() {
    //delete transitions;
}

void DFA::addTransition(int currentState, char symbol, int nextState) {
    transitions[std::make_pair(currentState, symbol)] = nextState;
}

void DFA::setStartState(int state) {
    startState = state;
}

void DFA::addAcceptState(int state) {
    acceptStates.insert(state);
}

bool DFA::isAcceptedState(int state) {
    return acceptStates.count(state) > 0;
}

int DFA::getStartState() {
    return startState;
}

std::vector<int> DFA::getNextState(int currentState, char symbol) {
    std::vector<int> result;
    result.push_back(transitions[std::make_pair(currentState, symbol)]);
    return result;
}

void DFA::generateTransitions(SyntaxNode * node) {
    if(node == nullptr) {
        return;
    }

    char value = node->getValue();
    //int currentState = getNextState(startState, value);
    //int nextState = getNextState(currentState, value);

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
