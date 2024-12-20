#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <stdexcept>

#ifndef syntax_node_hpp
#define syntax_node_hpp

class SyntaxNode {
public:
    char value;
    int minRepetitions;
    int maxRepetitions;
    SyntaxNode * left;
    SyntaxNode * right;

    SyntaxNode();
    SyntaxNode(char val);
    SyntaxNode(char val, SyntaxNode* child);
    SyntaxNode(char val, SyntaxNode* left, SyntaxNode* right);
    SyntaxNode(char val, int minRep, int maxRep, SyntaxNode* child);
    ~SyntaxNode();

    bool isOperator() const;
    int operatorPrecedence(char op) const;
};

#endif

#ifndef TREE_HPP
#define TREE_HPP

class SyntaxTree {
public:
    SyntaxNode * root;

    SyntaxTree(std::string regex);
    ~SyntaxTree();
    
    SyntaxNode * fromRegex(std::string regex);
};

#endif

#ifndef state_hpp
#define state_hpp

class State {
private:
    int id;
public:
    State();
    State(int id);

    int getId();
    void setId(int id);
};

#endif

#ifndef transition_hpp
#define transition_hpp

class Transition {
private:
    State from;
    char symbol;
    State to;
public:
    Transition();
    Transition(int from, int to, char symbol);
};

#endif

#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

class Automato {
public:
    SyntaxTree * syntaxTree;
    
    Automato(std::string regex);
    ~Automato();
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

    bool matches(std::string& input) const;
    std::pair<int, int> find(const std::string& input) const;
    std::vector<std::pair<int, int>> matchAll(const std::string& input) const;
    void replace(std::string& input, std::string replacement) const;
    bool isMatch(const std::string& input);
};
typedef Regex regex;

#endif
