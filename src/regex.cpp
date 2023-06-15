#include "regex.hpp"

Regex::Regex(std::string regex) {
    SyntaxTree * syntaxTree = new SyntaxTree();
    syntaxTree->build(regex);

    automato = new DFA(*syntaxTree);
    automato->generateTransitions(syntaxTree->getRoot());
}

Regex::~Regex() {
    delete (DFA*)automato;
}

bool Regex::match(std::string text) {
    return false;
}

std::vector<std::string> Regex::iterator(std::string text) {
    std::vector<std::string> result;
    //
    return result;
}
