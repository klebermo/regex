#include "nfa.hpp"

NFA::NFA() {
    //
}

NFA::~NFA() {
    //
}

NFA * NFA::build(std::string regex) {
    this->syntaxTree->buildTree(regex);
    SyntaxNode * node = this->syntaxTree->root;
    return this->build(node);
}

NFA * NFA::build(SyntaxNode * node) {
    if(!node) {
        throw std::invalid_argument("Invalid syntax tree node");
    }

    NFA * result = new NFA();

    NFA * baseNFA = this->build(node->left);
    NFA * empty = emptyNFA();

    switch(node->value) {
        case '/':
            //Union
            result =  this->unionNFA(this->build(node->left), this->build(node->right));
        case '.':
            //Concatenation
            result = this->concatenateNFA(this->build(node->left), this->build(node->right));
        case '*':
            //Kleene star
            result = this->kleeneStar(this->build(node->left));
        case '+':
            //Plus
            result =  this->unionNFA(baseNFA, kleeneStar(baseNFA));
        case '?':
            //Optional
            result = this->unionNFA(baseNFA, emptyNFA());
        case '^':
            //Anchor start
            result = this->anchorStart();
        case '$':
            //Anchor end
            result = this->anchorEnd();
        case '[':
            //Range start
            throw std::invalid_argument("Character ranges must be pre-processed.");
        case ']':
            //Range end
            throw std::invalid_argument("Character ranges must be pre-processed.");
        case '(':
            //Group start
            break;
        case ')':
            //Group end
            break;
        case '\n':
            //End of line
            break;
        case '{':
            //Repeat start
            for(int i = 0; i < node->minRepetitions; i++) {
                result = concatenateNFA(empty, baseNFA);
            }
            for(int i = node->minRepetitions; i < node->maxRepetitions; i++) {
                result = unionNFA(result, unionNFA(baseNFA, empty));
            }
        case '}':
            //Repeat end
            break;
        default:
            return this->fromLiteral(node->value);
    }

    return result;
}

void NFA::addTransition(int from, int to, char symbol) {
    std::pair<int, char> key = std::pair<int, char>(from, symbol);
    if(this->transitions.find(key) == this->transitions.end()) {
        this->transitions[key] = std::set<int>();
    }
    this->transitions[key].insert(to);
}

void NFA::setStartState(int state) {
    this->startStates.insert(state);
}

void NFA::setEndState(int state) {
    this->endStates.insert(state);
}

std::set<int> NFA::getStartStates() const {
    return this->startStates;
}

std::set<char> NFA::getAlphabet() const {
    std::set<char> alphabet;
    for(auto it = this->transitions.begin(); it != this->transitions.end(); it++) {
        alphabet.insert(it->first.second);
    }
    return alphabet;
}

std::map<std::pair<int, char>, std::set<int>> NFA::getTransitions() const {
    return this->transitions;
}

std::set<int> NFA::getEndStates() const {
    return this->endStates;
}

std::vector<int> NFA::getNextState(int state, char symbol) const {
    std::pair<int, char> key = std::pair<int, char>(state, symbol);
    if(this->transitions.find(key) == this->transitions.end()) {
        return std::vector<int>();
    }
    std::vector<int> result;
    for(auto it = this->transitions.at(key).begin(); it != this->transitions.at(key).end(); it++) {
        result.push_back(*it);
    }
    return result;
}

NFA * NFA::emptyNFA() {
    NFA * nfa = new NFA();
    nfa->setStartState(0);
    nfa->setEndState(1);
    return nfa;
}

NFA * NFA::unionNFA(NFA * nfa1, NFA * nfa2) {
    NFA * result = new NFA();
    int offset = nfa1->transitions.size();
    for(auto it = nfa1->transitions.begin(); it != nfa1->transitions.end(); it++) {
        result->addTransition(it->first.first + 1, it->first.first + offset, it->first.second);
    }
    for(auto it = nfa2->transitions.begin(); it != nfa2->transitions.end(); it++) {
        result->addTransition(it->first.first + offset, it->first.first + offset, it->first.second);
    }
    result->setStartState(0);
    result->setEndState(offset + nfa2->transitions.size() + 1);
    return result;
}

NFA * NFA::concatenateNFA(NFA * nfa1, NFA * nfa2) {
    NFA * result = new NFA();
    int offset = nfa1->transitions.size();
    for(auto it = nfa1->transitions.begin(); it != nfa1->transitions.end(); it++) {
        result->addTransition(it->first.first, it->first.first, it->first.second);
    }
    for(auto it = nfa2->transitions.begin(); it != nfa2->transitions.end(); it++) {
        result->addTransition(it->first.first + offset, it->first.first + offset, it->first.second);
    }
    result->setStartState(0);
    result->setEndState(offset + nfa2->transitions.size() + 1);
    return result;
}

NFA * NFA::kleeneStar(NFA * nfa) {
    NFA * result = new NFA();
    int offset = this->transitions.size();
    for(auto it = this->transitions.begin(); it != this->transitions.end(); it++) {
        result->addTransition(it->first.first + 1, it->first.first + offset, it->first.second);
    }
    for(auto it = nfa->transitions.begin(); it != nfa->transitions.end(); it++) {
        result->addTransition(it->first.first + offset, it->first.first + offset, it->first.second);
    }
    result->setStartState(0);
    result->setEndState(offset + nfa->transitions.size() + 1);
    return result;
}

NFA * NFA::anchorStart() {
    NFA * result = new NFA();
    result->addTransition(0, 1, '^');
    return result;
}

NFA * NFA::anchorEnd() {
    NFA * result = new NFA();
    result->addTransition(0, 1, '$');
    return result;
}

NFA * NFA::fromLiteral(char literal) {
    NFA * result = new NFA();
    result->addTransition(0, 1, literal);
    return result;
}
