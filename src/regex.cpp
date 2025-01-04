#include "regex.hpp"

Regex::Regex(std::string regex) {
    automato = new Automato(regex);
    automato->buildTransitions();
}

Regex::~Regex() {
    delete automato;
}

bool Regex::matches(std::string& input) {
    std::unordered_set<int> currentStates; 
    std::unordered_set<int> nextStates;

    // Consuma cada caractere da entrada
    for (char c : input) {
        nextStates.clear();

        // Verifique todas as transições possíveis a partir dos estados ativos
        for (int state : currentStates) {
            for (auto transition : automato->getTransitions()) {
                if (transition._from() == state && transition._symbol() == c) {
                    nextStates.insert(transition._to());
                }
            }
        }

        // Realize o fechamento epsilon nos estados resultantes
        nextStates = automato->epsilonClosure(nextStates);

        // Atualize os estados ativos
        currentStates = nextStates;

        // Se não houver estados ativos, a entrada não corresponde
        if (currentStates.empty()) {
            return false;
        }
    }

    // Verifique se algum estado ativo é um estado final
    for (int state : currentStates) {
        if (state == automato->getFinalState()) { // Supondo que 'finalState' é o estado final do automato
            return true;
        }
    }

    return false;
}

std::pair<int, int> Regex::find(const std::string& input) {
    if (automato->getTransitions().empty()) return {-1, -1}; // Se não houver transições, retorna inválido
    std::vector<std::pair<int, int>> acceptedStates;

    // Iterar pela entrada para iniciar o reconhecimento em diferentes posições
    for (size_t start = 0; start < input.size(); start++) {
        std::unordered_set<int> currentStates;
        std::unordered_set<int> nextStates;

        // Inicialize os estados ativos com o fechamento epsilon do estado inicial
        currentStates.insert(0);
        currentStates = automato->epsilonClosure(currentStates);

        // Verifique a partir da posição `start` na entrada
        for (size_t i = start; i < input.size(); i++) {
            char c = input[i];
            nextStates.clear();

            // Realize transições baseadas no caractere atual
            for (int state : currentStates) {
                for (auto transition : automato->getTransitions()) {
                    if (transition._from() == state && transition._symbol() == c) {
                        nextStates.insert(transition._to());
                    }
                }
            }

            // Realize o fechamento epsilon nos estados resultantes
            nextStates = automato->epsilonClosure(nextStates);
            currentStates = nextStates;

            // Se alcançarmos o estado final, retornamos a correspondência
            if (currentStates.find(automato->getFinalState()) != currentStates.end()) {
                return {static_cast<int>(start), static_cast<int>(i)};
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

std::vector<std::pair<int, int>> Regex::matchAll(const std::string& input) {
    std::vector<std::pair<int, int>> matches;
    std::vector<std::pair<int, int>> acceptedStates;

    if (automato->getTransitions().empty()) return matches; // Retorna vazio se não houver transições

    // Iterar pela entrada para encontrar todas as correspondências
    for (size_t start = 0; start < input.size(); start++) {
        std::unordered_set<int> currentStates;
        std::unordered_set<int> nextStates;

        // Inicialize os estados ativos com o fechamento epsilon do estado inicial
        currentStates.insert(0);
        currentStates = automato->epsilonClosure(currentStates);

        // Verifique a partir da posição `start` na entrada
        for (size_t i = start; i < input.size(); i++) {
            char c = input[i];
            nextStates.clear();

            // Realize transições baseadas no caractere atual
            for (int state : currentStates) {
                for (auto transition : automato->getTransitions()) {
                    if (transition._from() == state && transition._symbol() == c) {
                        nextStates.insert(transition._to());
                    }
                }
            }

            // Realize o fechamento epsilon nos estados resultantes
            nextStates = automato->epsilonClosure(nextStates);
            currentStates = nextStates;

            // Se alcançarmos o estado final, adicionamos a correspondência
            if (currentStates.find(automato->getFinalState()) != currentStates.end()) {
                matches.emplace_back(static_cast<int>(start), static_cast<int>(i));
                break; // Para esta posição inicial, pare ao encontrar a primeira correspondência
            }

            // Se não houver estados ativos, interrompa esta tentativa
            if (currentStates.empty()) {
                break;
            }
        }
    }

    return matches;
}

void Regex::replace(std::string& input, std::string replacement) {
    if (automato->getTransitions().empty()) return; // Não há transições, nada a substituir

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
    if (automato->getTransitions().empty()) return false; // Não há transições, nenhuma correspondência é possível.

    // Estados iniciais e finais do autômato
    int initialState = 0;
    std::unordered_set<int> currentStates = automato->epsilonClosure({initialState});

    for (char c : input) {
        std::unordered_set<int> nextStates;

        // Processa as transições para o caractere atual
        for (int state : currentStates) {
            for (auto transition : automato->getTransitions()) {
                if (transition._from() == state && (transition._symbol() == c || transition._symbol() == '\0')) {
                    nextStates.insert(transition._to());
                }
            }
        }

        // Atualiza os estados atuais com a fecho-ε dos próximos estados
        currentStates = automato->epsilonClosure(nextStates);
    }

    // Verifica se algum dos estados finais foi atingido após processar toda a string
    return currentStates.count(automato->getFinalState()) > 0;
}
