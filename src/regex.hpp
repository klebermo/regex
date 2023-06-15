#ifndef regex_hpp
#define regex_hpp

#include "dfa.hpp"
#include "nfa.hpp"

class Regex {
private:
    Automato * automato;
public:
    Regex(std::string regex);
    ~Regex();
    bool match(std::string text);
    std::vector<std::string> iterator(std::string text);

};
typedef Regex regex;

#endif
