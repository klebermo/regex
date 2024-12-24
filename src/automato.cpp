#include "automato.hpp"

Automato::Automato(std::string regex) {
    syntaxTree = new SyntaxTree(regex);
}

Automato::~Automato() {
    delete syntaxTree;
}

SyntaxTree * Automato::getSyntaxTree() {
    return this->syntaxTree;
}
