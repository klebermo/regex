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
private:
    char value;
    SyntaxNode * left;
    SyntaxNode * right;
public:
    SyntaxNode();
    SyntaxNode(char val);
    SyntaxNode(char val, SyntaxNode* child);
    SyntaxNode(char val, SyntaxNode* left, SyntaxNode* right);
    ~SyntaxNode();

    char _value();
    SyntaxNode * _left();
    void _left(SyntaxNode * node);
    SyntaxNode * _right();
    void _right(SyntaxNode * node);
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

    void print();
    void print(SyntaxNode * node, int level);
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
private:
    SyntaxTree * syntaxTree;
    std::vector<Transition> transitions;
    int finalState;

    std::pair<int, int> buildTransitions(SyntaxNode * node, int stateCounter);
    void addTransition(int from, int to, char value);    
public:
    Automato(std::string regex);
    ~Automato();

    void buildTransitions();
    void printTransitions();
    std::vector<Transition> getTransitions();
    int getFinalState();

    std::unordered_set<int> epsilonClosure(const std::unordered_set<int>& states) const;
};

#endif

#ifndef regex_hpp
#define regex_hpp

class Regex {
private:
    Automato * automato;    
public:
    Regex(std::string regex);
    ~Regex();

    bool matches(std::string& input);
    std::pair<int, int> find(const std::string& input);
    std::vector<std::pair<int, int>> matchAll(const std::string& input);
    void replace(std::string& input, std::string replacement);
    bool isMatch(const std::string& input);
};

#endif
