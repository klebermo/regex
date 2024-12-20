#include "transition.hpp"

State::State() {
    this->id = 0;
}

State::State(int id) {
    this->id = id;
}

int State::getId() {
    return this->id;
}

void State::setId(int id) {
    this->id = id;
}

Transition::Transition() {
    this->from.setId(0);
    this->to.setId(0);
    this->symbol = '\0';
}

Transition::Transition(int from, int to, char symbol) {
    this->from.setId(from);
    this->to.setId(to);
    this->symbol = symbol;
}
