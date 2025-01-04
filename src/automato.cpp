#include "automato.hpp"

Automato::Automato(std::string regex) {
    syntaxTree = new SyntaxTree(regex);
}

Automato::~Automato() {
    delete syntaxTree;
}

std::unordered_set<int> Automato::epsilonClosure(const std::unordered_set<int>& states) const {
        std::unordered_set<int> closure = states;
        std::stack<int> stack;

        for (int state : states) {
            stack.push(state);
        }

        while (!stack.empty()) {
            int state = stack.top();
            stack.pop();

            for (auto transition : transitions) {
                if (transition._from() == state && transition._symbol() == '\0') {
                    if (closure.find(transition._to()) == closure.end()) {
                        closure.insert(transition._to());
                        stack.push(transition._to());
                    }
                }
            }
        }

        return closure;
}

void Automato::addTransition(int from, int to, char value) {
    this->transitions.push_back(Transition(from, to, value));
}

void Automato::buildTransitions() {
    buildTransitions(syntaxTree->getRoot(), 0);
    printTransitions();
}

void Automato::printTransitions() {
    for(auto transition : transitions) {
        std::cout << transition._from() << " -> " << transition._to() << " : " << transition._symbol() << std::endl;
    }
}

std::vector<Transition> Automato::getTransitions() {
    return transitions;
}

int Automato::getFinalState() {
    return finalState;
}

std::pair<int, int> Automato::buildTransitions(SyntaxNode * node, int stateCounter) {
    if(node == nullptr) return {-1, -1};

    int start = stateCounter++;
    int end = stateCounter++;
    finalState = end;

    char c = node->_value();
    switch(c) {
            case '[':
                {
                    auto left = buildTransitions(node->_left(), stateCounter);
                    auto right = buildTransitions(node->_right(), stateCounter);

                    addTransition(start, left.first, '\0');
                    addTransition(left.second, right.first, '\0');
                    addTransition(right.second, end, '\0');
                    break;
                }
            case '.':
                {
                    auto left = buildTransitions(node->_left(), stateCounter);
                    auto right = buildTransitions(node->_right(), stateCounter);

                    addTransition(start, left.first, '\0');
                    addTransition(left.second, right.first, '\0');
                    addTransition(right.second, end, '\0');
                    break;
                }
            case '^':
                {
                    auto left = buildTransitions(node->_left(), stateCounter);
                    auto right = buildTransitions(node->_right(), stateCounter);

                    addTransition(start, left.first, '\0');
                    addTransition(left.second, right.first, '\0');
                    addTransition(right.second, end, '\0');
                    break;
                }
            case '$':
                {
                    auto left = buildTransitions(node->_left(), stateCounter);
                    auto right = buildTransitions(node->_right(), stateCounter);

                    addTransition(start, left.first, '\0');
                    addTransition(left.second, right.first, '\0');
                    addTransition(right.second, end, '\0');
                    break;
                }
            case '(':
                {
                    auto left = buildTransitions(node->_left(), stateCounter);
                    auto right = buildTransitions(node->_right(), stateCounter);

                    addTransition(start, left.first, '\0');
                    addTransition(left.second, right.first, '\0');
                    addTransition(right.second, end, '\0');
                    break;
                }
            case '*':
                {
                    auto child = buildTransitions(node->_left(), stateCounter);

                    addTransition(start, child.first, '\0');
                    addTransition(child.second, child.first, '\0');
                    addTransition(child.second, end, '\0');
                    addTransition(start, end, '\0');
                    break;
                }                
            case '+':
                {
                    auto child = buildTransitions(node->_left(), stateCounter);

                    addTransition(start, child.first, '\0');
                    addTransition(child.second, child.first, '\0');
                    addTransition(child.second, end, '\0');
                    break;
                }
            case '?':
                {
                    auto child = buildTransitions(node->_left(), stateCounter);

                    addTransition(start, child.first, '\0');
                    addTransition(child.second, end, '\0');
                    addTransition(start, end, '\0');
                    break;
                }                
            case '{':
                {
                    int minRepeats = node->_left()->_value() - '0';
                    int maxRepeats = node->_right()->_value() - '0';

                    int prevEnd = start;
                    for (int i = 0; i < minRepeats; i++) {
                        auto child = buildTransitions(node->_left(), stateCounter);
                        addTransition(prevEnd, child.first, '\0');
                        prevEnd = child.second;
                    }

                    if (maxRepeats == -1) {
                        auto child = buildTransitions(node->_left(), stateCounter);
                        addTransition(prevEnd, child.first, '\0');
                        addTransition(child.second, end, '\0');
                    } else {
                        for (int i = minRepeats; i < maxRepeats; i++) {
                            auto child = buildTransitions(node->_left(), stateCounter);
                            addTransition(prevEnd, child.first, '\0');
                            addTransition(child.second, end, '\0');
                            prevEnd = child.second;
                        }
                    }

                    addTransition(prevEnd, end, '\0');
                    break;
                }                
            case '|':
                {
                    auto left = buildTransitions(node->_left(), stateCounter);
                    auto right = buildTransitions(node->_right(), stateCounter);

                    addTransition(start, left.first, '\0');
                    addTransition(start, right.first, '\0');
                    addTransition(left.second, end, '\0');
                    addTransition(right.second, end, '\0');
                    break;
                }
            case '-':
                {
                    for(char ch = node->_left()->_value(); ch <= node->_right()->_value(); ch++) {
                        addTransition(start, stateCounter, ch);
                        stateCounter++;
                    }
                    break;
                }
            default:
                {
                    addTransition(start, end, c);
                    break;
                }
    }

    return {start, end};
}
