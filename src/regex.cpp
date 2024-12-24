#include "regex.hpp"

Regex::Regex(std::string regex) {
    automato = new Automato(regex);
    buildTransitions(automato->getSyntaxTree()->getRoot(), 0);
}

Regex::~Regex() {
    delete automato;
}

std::unordered_set<int> Regex::epsilonClosure(const std::unordered_set<int>& states) const {
        std::unordered_set<int> closure = states;
        std::stack<int> stack;

        for (int state : states) {
            stack.push(state);
        }

        while (!stack.empty()) {
            int state = stack.top();
            stack.pop();

            for (auto transition : transitions) {
                if (transition._from() == state && transition._symbol() == '\0') {
                    if (closure.find(transition._to()) == closure.end()) {
                        closure.insert(transition._to());
                        stack.push(transition._to());
                    }
                }
            }
        }

        return closure;
}

bool Regex::matches(std::string& input) const {
    std::unordered_set<int> currentStates; 
    std::unordered_set<int> nextStates;

    // Consuma cada caractere da entrada
    for (char c : input) {
        nextStates.clear();

        // Verifique todas as transições possíveis a partir dos estados ativos
        for (int state : currentStates) {
            for (auto transition : transitions) {
                if (transition._from() == state && transition._symbol() == c) {
                    nextStates.insert(transition._to());
                }
            }
        }

        // Realize o fechamento epsilon nos estados resultantes
        nextStates = epsilonClosure(nextStates);

        // Atualize os estados ativos
        currentStates = nextStates;

        // Se não houver estados ativos, a entrada não corresponde
        if (currentStates.empty()) {
            return false;
        }
    }

    // Verifique se algum estado ativo é um estado final
    for (int state : currentStates) {
        if (state == finalState) { // Supondo que 'finalState' é o estado final do automato
            return true;
        }
    }

    return false;
}

std::pair<int, int> Regex::find(const std::string& input) const {
    if (transitions.empty()) return {-1, -1}; // Se não houver transições, retorna inválido

    // Iterar pela entrada para iniciar o reconhecimento em diferentes posições
    for (size_t start = 0; start < input.size(); ++start) {
        std::unordered_set<int> currentStates;
        std::unordered_set<int> nextStates;

        // Inicialize os estados ativos com o fechamento epsilon do estado inicial
        currentStates.insert(0);
        currentStates = epsilonClosure(currentStates);

        // Verifique a partir da posição `start` na entrada
        for (size_t i = start; i < input.size(); ++i) {
            char c = input[i];
            nextStates.clear();

            // Realize transições baseadas no caractere atual
            for (int state : currentStates) {
                for (auto transition : transitions) {
                    if (transition._from() == state && transition._symbol() == c) {
                        nextStates.insert(transition._to());
                    }
                }
            }

            // Realize o fechamento epsilon nos estados resultantes
            nextStates = epsilonClosure(nextStates);
            currentStates = nextStates;

            // Se alcançarmos o estado final, retornamos a correspondência
            if (currentStates.find(finalState) != currentStates.end()) {
                //return {static_cast<int>(start), static_cast<int>(i + 1)};
                return {start, i+1};
            }

            // Se não houver estados ativos, interrompa esta tentativa
            if (currentStates.empty()) {
                break;
            }
        }
    }

    // Se nenhuma correspondência for encontrada, retorna inválido
    return {-1, -1};
}

std::vector<std::pair<int, int>> Regex::matchAll(const std::string& input) const {
    std::vector<std::pair<int, int>> output;

    if (transitions.empty()) return output; // Retorna vazio se não houver transições

    // Iterar pela entrada para encontrar todas as correspondências
    for (size_t start = 0; start < input.size(); start++) {
        std::unordered_set<int> currentStates;
        std::unordered_set<int> nextStates;

        // Inicialize os estados ativos com o fechamento epsilon do estado inicial
        currentStates.insert(0);
        currentStates = epsilonClosure(currentStates);

        // Verifique a partir da posição `start` na entrada
        for (size_t i = start; i < input.size(); i++) {
            char c = input[i];
            nextStates.clear();

            // Realize transições baseadas no caractere atual
            for (int state : currentStates) {
                for (auto transition : transitions) {
                    if (transition._from() == state && transition._symbol() == c) {
                        nextStates.insert(transition._to());
                    }
                }
            }

            // Realize o fechamento epsilon nos estados resultantes
            nextStates = epsilonClosure(nextStates);
            currentStates = nextStates;

            // Se alcançarmos o estado final, adicionamos a correspondência
            if (currentStates.find(finalState) != currentStates.end()) {
                //output.emplace_back(static_cast<int>(start), static_cast<int>(i + 1));
                output.push_back({start, i+1});
                break; // Para esta posição inicial, pare ao encontrar a primeira correspondência
            }

            // Se não houver estados ativos, interrompa esta tentativa
            if (currentStates.empty()) {
                break;
            }
        }
    }

    return output;
}

void Regex::replace(std::string& input, std::string replacement) const {
    if (transitions.empty()) return; // Não há transições, nada a substituir

    std::vector<std::pair<int, int>> matches = matchAll(input);

    // Ajustar as substituições do final para o início, para evitar interferências nos índices
    int offset = 0;
    for (const auto& match : matches) {
        int start = match.first + offset;
        int end = match.second + offset;

        // Substituir a substring correspondente pelo padrão de substituição
        input.replace(start, end - start, replacement);

        // Atualizar o deslocamento devido à substituição
        offset += replacement.size() - (end - start);
    }
}

bool Regex::isMatch(const std::string& input) {
    if (transitions.empty()) return false; // Não há transições, nenhuma correspondência é possível.

    // Estados iniciais e finais do autômato
    int initialState = 0;
    std::unordered_set<int> currentStates = epsilonClosure({initialState});

    for (char c : input) {
        std::unordered_set<int> nextStates;

        // Processa as transições para o caractere atual
        for (int state : currentStates) {
            for (auto transition : transitions) {
                if (transition._from() == state && (transition._symbol() == c || transition._symbol() == '\0')) {
                    nextStates.insert(transition._to());
                }
            }
        }

        // Atualiza os estados atuais com a fecho-ε dos próximos estados
        currentStates = epsilonClosure(nextStates);
    }

    // Verifica se algum dos estados finais foi atingido após processar toda a string
    return currentStates.count(finalState) > 0;
}

void Regex::addTransition(int from, int to, char symbol) {
    transitions.push_back(Transition(from, to, symbol));
}

std::pair<int, int> regex::buildTransitions(SyntaxNode * node, int stateCounter) {
    if(!node) return {-1, -1};

    int start = stateCounter++;
    int end = stateCounter++;

    switch(node->_value()) {
        case '|':
            {
                auto left = buildTransitions(node->_left(), stateCounter);
                auto right = buildTransitions(node->_right(), stateCounter);
                addTransition(start, left.first, '\0'); // Transição epsilon para o início do ramo esquerdo
                addTransition(start, right.first, '\0'); // Transição epsilon para o início do ramo direito
                addTransition(left.second, end, '\0'); // Transição epsilon do fim do ramo esquerdo para o fim
                addTransition(right.second, end, '\0'); // Transição epsilon do fim do ramo direito para o fim
                break;
            }
        case '.':
            {
                auto left = buildTransitions(node->_left(), stateCounter);
                auto right = buildTransitions(node->_right(), stateCounter);

                addTransition(start, left.first, '\0'); // Transição epsilon para o início do ramo esquerdo
                addTransition(left.second, right.first, '\0'); // Conexão entre os ramos
                addTransition(right.second, end, '\0'); // Transição epsilon do fim do ramo direito para o fim
                break;
            }
        case '^':
            {
                addTransition(start, end, '^');
                break;
            }
        case '$':
            {
                addTransition(start, end, '$');
                break;
            }
        case '-':
            {
                for(char ch = node->_left()->_value(); ch <= node->_right()->_value(); ++ch) {
                    addTransition(start, end, ch);
                }
                break;
            }
        case '*':
            {
                auto child = buildTransitions(node->_left(), stateCounter);

                addTransition(start, child.first, '\0'); // Transição epsilon para o início do filho
                addTransition(child.second, child.first, '\0'); // Ciclo para repetição
                addTransition(child.second, end, '\0'); // Transição epsilon para o fim
                addTransition(start, end, '\0'); // Transição epsilon para representar 0 ocorrências
                break;
            }
        case '+':
            {
                auto child = buildTransitions(node->_left(), stateCounter);

                addTransition(start, child.first, '\0'); // Transição epsilon para o início do filho
                addTransition(child.second, child.first, '\0'); // Ciclo para repetição
                addTransition(child.second, end, '\0'); // Transição epsilon para o fim
                break;
            }
        case '?':
            {
                auto child = buildTransitions(node->_left(), stateCounter);

                addTransition(start, child.first, '\0'); // Transição epsilon para o início do filho
                addTransition(child.second, end, '\0'); // Transição epsilon para o fim
                addTransition(start, end, '\0'); // Transição epsilon para representar 0 ocorrências
                break;
            }
        case '{':
            {
                int minRepeats = node->_left()->_value() - '0'; // Valor mínimo de repetições
                int maxRepeats = node->_right()->_value() - '0'; // Valor máximo de repetições

                int prevEnd = start;
                for (int i = 0; i < minRepeats; ++i) {
                    auto child = buildTransitions(node->_left(), stateCounter);
                    addTransition(prevEnd, child.first, '\0');
                    prevEnd = child.second;
                }

                if (maxRepeats > minRepeats) {
                    for (int i = minRepeats; i < maxRepeats; ++i) {
                        auto child = buildTransitions(node->_left(), stateCounter);
                        addTransition(prevEnd, child.first, '\0');
                        addTransition(child.second, end, '\0');
                    }
                }

                addTransition(prevEnd, end, '\0'); // Conexão final
                break;
            }
        default:
            addTransition(start, end, node->_value());
            break;
    }

    finalState = end;
    return {start, end};
}
