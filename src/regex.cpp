#include "regex.hpp"

Regex::Regex(std::string regex) {
    automato = new Automato(regex);
}

Regex::~Regex() {
    delete automato;
}

int regex_search(std::string input, Matches matches, Regex regex) {
    return 0;
}
