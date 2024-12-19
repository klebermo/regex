#include "regex.hpp"

Regex::Regex(std::string regex) {
    nfa = new NFA();
    SyntaxTree * syntaxTree = new SyntaxTree();
    syntaxTree->buildTree(regex);
    nfa = nfa->build(syntaxTree->root);
}

Regex::~Regex() {
    delete nfa;
}

bool Regex::matches(const std::string& input) {
    std::set<int> currentStates = nfa->getStartStates();
    for(std::string::size_type i = 0; i < input.size(); i++) {
        std::set<int> nextStates;
        for(auto it = currentStates.begin(); it != currentStates.end(); it++) {
            std::vector<int> states = nfa->getNextState(*it, input[i]);
            for(std::vector<int>::size_type j = 0; j < states.size(); j++) {
                nextStates.insert(states[j]);
            }
        }
        currentStates = nextStates;
    }
    for(auto it = currentStates.begin(); it != currentStates.end(); it++) {
        if(nfa->getEndStates().find(*it) != nfa->getEndStates().end()) {
            return true;
        }
    }
    return false;
}

std::pair<int, int> Regex::find(const std::string& input) {
    for(std::string::size_type i = 0; i < input.size(); i++) {
        if(matches(input.substr(i))) {
            return std::pair<int, int>(i, i + 1);
        }
    }
    return std::pair<int, int>(-1, -1);
}

std::vector<std::pair<int, int>> Regex::matchAll(const std::string& input) {
    std::vector<std::pair<int, int>> result;
    for(std::string::size_type i = 0; i < input.size(); i++) {
        std::pair<int, int> match = find(input.substr(i));
        if(match.first != -1) {
            result.push_back(std::pair<int, int>(i + match.first, i + match.second));
        }
    }
    return result;
}

std::string Regex::replace(const std::string& input, const std::string& replacement) {
    std::string result;
    std::vector<std::pair<int, int>> matches = matchAll(input);
    int last = 0;
    for(std::vector<std::pair<int, int>>::size_type i = 0; i < matches.size(); i++) {
        result += input.substr(last, matches[i].first - last);
        result += replacement;
        last = matches[i].second;
    }
    result += input.substr(last);
    return result;
}

bool Regex::isMatch(const std::string& input) {
    return matches(input);
}
