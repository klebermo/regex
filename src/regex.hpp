#ifndef regex_hpp
#define regex_hpp

#include "automato.hpp"

class Regex {
private:
    Automato * automato;    
public:
    Regex(std::string regex);
    ~Regex();

    bool matches(std::string& input);
    std::pair<int, int> find(const std::string& input);
    std::vector<std::pair<int, int>> matchAll(const std::string& input);
    void replace(std::string& input, std::string replacement);
    bool isMatch(const std::string& input);
};

#endif
