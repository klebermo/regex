#include "regex.hpp"

Regex::Regex(std::string regex) {
    automato = new Automato(regex);
    buildTransitions(automato->syntaxTree->root, 0);
}

Regex::~Regex() {
    delete automato;
}

bool Regex::matches(std::string& input) const {
    return false;
}

std::pair<int, int> Regex::find(const std::string& input) const {
    return {0, 0};
}

std::vector<std::pair<int, int>> Regex::matchAll(const std::string& input) const {
    return {};
}

void Regex::replace(std::string& input, std::string replacement) const {
}

bool Regex::isMatch(const std::string& input) {
    return false;
}

void Regex::addTransition(int from, int to, char symbol) {
    transitions.push_back(Transition(from, to, symbol));
}

std::pair<int, int> regex::buildTransitions(const SyntaxNode * node, int stateCounter) {
    if(!node) return {-1, -1};

    int start = stateCounter++;
    int end = stateCounter++;

    switch(node->value) {
        case '|':
            break;
        case '.':
            break;
        case '^':
            break;
        case '$':
            break;
        case '-':
            break;
        case '*':
            break;
        case '+':
            break;
        case '?':
            break;
        case '{':
            break;
        case '}':
            break;
        default:
            addTransition(start, end, node->value);

            buildTransitions(node->left, stateCounter);
            buildTransitions(node->right, stateCounter);
            break;
    }

    return {start, end};
}
