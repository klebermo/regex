#include "automato.hpp"

Automato::Automato() {
    this->syntaxTree = new SyntaxTree();
}

Automato::~Automato() {
    delete this->syntaxTree;
}
