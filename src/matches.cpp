#include "matches.hpp"

Matches::Matches() {
    counter = 0;
}

Matches::~Matches() {
    //
}

void Matches::addTransition(int from, int to, char symbol, bool isFinal) {
    transitions.push_back(Transition(from, to, symbol, isFinal));
}

std::string Matches::operator[](int index) const {
    return "...";
}
