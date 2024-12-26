#include "regex.hpp"

Regex::Regex(std::string regex) {
    automato = new Automato(regex);
    automato->buildTransitions();
}

Regex::~Regex() {
    delete automato;
}

bool Regex::matches(std::string& input) {
    return automato->matches(input);
}

std::pair<int, int> Regex::find(const std::string& input) {
    return automato->find(input);
}

std::vector<std::pair<int, int>> Regex::matchAll(const std::string& input) {
    return automato->matchAll(input);
}

void Regex::replace(std::string& input, std::string replacement) {
    return automato->replace(input, replacement);
}

bool Regex::isMatch(const std::string& input) {
    return automato->isMatch(input);
}
