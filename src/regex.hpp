#ifndef regex_hpp
#define regex_hpp

#include "dfa.hpp"
#include "nfa.hpp"

enum Type {
    dfa,
    nfa
};

class Regex {
private:
    SyntaxTree * syntaxTree;
    Automato * automato;
    Type type;
public:
    Regex(std::string regex);
    ~Regex();
    bool match(std::string text);
    std::vector<std::string> iterator(std::string text);

};
typedef Regex regex;

#endif
