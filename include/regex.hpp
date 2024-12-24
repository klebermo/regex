#include <string>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <stdexcept>
#include <iostream>

#ifndef syntax_node_hpp
#define syntax_node_hpp

class SyntaxNode {
    char value;
    int minRepetitions;
    int maxRepetitions;
    SyntaxNode * left;
    SyntaxNode * right;
public:
    SyntaxNode();
    SyntaxNode(char val);
    SyntaxNode(char val, SyntaxNode* child);
    SyntaxNode(char val, SyntaxNode* left, SyntaxNode* right);
    SyntaxNode(char val, int minRep, int maxRep, SyntaxNode* child);
    ~SyntaxNode();

    char _value();
    int _minRepetitions();
    int _maxRepetitions();
    SyntaxNode * _left();
    SyntaxNode * _right();

    bool isOperator() const;
    int precedence(char op) const;
};

#endif

#ifndef TREE_HPP
#define TREE_HPP

class SyntaxTree {
    SyntaxNode * root;
public:
    SyntaxTree(std::string regex);
    ~SyntaxTree();

    SyntaxNode * getRoot();
    SyntaxNode * fromRegex(std::string regex);
};

#endif

#ifndef state_hpp
#define state_hpp

class State {
    int id;
public:
    State();
    State(int id);

    int getId();
};

#endif

#ifndef transition_hpp
#define transition_hpp

class Transition {
    State from;
    char symbol;
    State to;
public:
    Transition();
    Transition(int from, int to, char symbol);

    int _from();
    char _symbol();
    int _to();
};

#endif

#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

class Automato {
    SyntaxTree * syntaxTree;
public:
    Automato(std::string regex);
    ~Automato();

    SyntaxTree * getSyntaxTree();
};

#endif

#ifndef regex_hpp
#define regex_hpp

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
