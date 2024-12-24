#ifndef syntax_node_hpp
#define syntax_node_hpp

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

const char operators[] = {'[', ']', '.', '^', '$', '(', ')', '*', '+', '?', '{', '}', '|'};
const int operatorsSize = 14;

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
