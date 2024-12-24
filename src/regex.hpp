#ifndef regex_hpp
#define regex_hpp

#include "automato.hpp"
#include "transition.hpp"

class Regex {
private:
    Automato * automato;
    std::vector<Transition> transitions;
    int finalState;

    std::pair<int, int> buildTransitions(SyntaxNode * node, int stateCounter = 0);
    void addTransition(int from, int to, char symbol); 
    std::unordered_set<int> epsilonClosure(const std::unordered_set<int>& states) const;
public:
    Regex(std::string regex);
    ~Regex();

    bool matches(std::string& input) const;
    std::pair<int, int> find(const std::string& input) const;
    std::vector<std::pair<int, int>> matchAll(const std::string& input) const;
    void replace(std::string& input, std::string replacement) const;
    bool isMatch(const std::string& input);
};
typedef Regex regex;

#endif
