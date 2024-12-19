#ifndef regex_hpp
#define regex_hpp

#include "dfa.hpp"

class Regex {
private:
    NFA * nfa;
public:
    Regex(std::string regex);
    ~Regex();

    bool matches(const std::string& input);
    std::pair<int, int> find(const std::string& input);
    std::vector<std::pair<int, int>> matchAll(const std::string& input);
    std::string replace(const std::string& input, const std::string& replacement);
    bool isMatch(const std::string& input);
};

#endif
