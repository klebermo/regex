#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "syntax_tree.hpp"

class Automato {
public:
    SyntaxTree * syntaxTree;
    
    Automato(std::string regex);
    ~Automato();
};

#endif
