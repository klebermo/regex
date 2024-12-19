#ifndef regex_hpp
#define regex_hpp

#include "automato.hpp"

class Regex {
private:
    Automato * automato;
public:
    Regex(std::string regex);
    ~Regex();

    Automato * getAutomato() const { return automato; }
};
typedef Regex regex;

int regex_search(std::string input, Matches matches, Regex regex);

#endif
