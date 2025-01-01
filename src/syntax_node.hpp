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
#include <algorithm>
#include <iostream>

const char operators[] = {'[', ']', '.', '^', '$', '(', ')', '*', '+', '?', '{', '}', '|'};
const int operatorsSize = 14;
int precedence(char op);
bool isOperator(char c);

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
