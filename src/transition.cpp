#include "transition.hpp"

State::State() {
    this->id = 0;
}

State::State(int id) {
    this->id = id;
}

Transition::Transition() {
    this->from = 0;
    this->to = 0;
    this->symbol = ' ';
}

Transition::Transition(int from, int to, char symbol) {
    this->from = from;
    this->to = to;
    this->symbol = symbol;
}
