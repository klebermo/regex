#ifndef matches_hpp
#define matches_hpp

#include "transition.hpp"

class Matches {
private:
    std::vector<Transition> transitions;
    int counter;
public:
    Matches();
    ~Matches();

    void addTransition(int from, int to, char symbol, bool isFinal);
    std::string operator[](int index) const;
};
typedef Matches smatches;

#endif
