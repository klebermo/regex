#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

#include "matches.hpp"

class Automato {
private:
    SyntaxTree * syntaxTree;
public:
    Automato(std::string regex);
    ~Automato();
};

#endif
