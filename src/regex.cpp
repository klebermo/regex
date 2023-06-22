#include "regex.hpp"

Regex::Regex(std::string regex) {
    syntaxTree = new SyntaxTree();
    syntaxTree->build(regex);
    automato = nullptr;
}

Regex::~Regex() {
    if(type == dfa)
        delete (DFA*)automato;
    else
        delete (NFA*)automato;
}

bool Regex::match(std::string text) {
    if(automato != nullptr)
        delete automato;
    
    automato = new DFA(*syntaxTree);
    type = dfa;
    automato->generateTransitions(syntaxTree->getRoot());

    return false;
}

std::vector<std::string> Regex::iterator(std::string text) {
    if(automato != nullptr)
        delete automato;
    
    automato = new NFA(*syntaxTree);
    type = nfa;
    automato->generateTransitions(syntaxTree->getRoot());

    std::vector<std::string> result;
    //
    return result;
}
