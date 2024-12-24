#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "syntax_tree.hpp"

class Automato {
    SyntaxTree * syntaxTree;
public:
    Automato(std::string regex);
    ~Automato();

    SyntaxTree * getSyntaxTree();
};

#endif
