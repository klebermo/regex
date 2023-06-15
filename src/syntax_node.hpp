#ifndef syntax_node_hpp
#define syntax_node_hpp

#include <cctype>

const char operators[] = {'^', '.', '[', ']', '$', '(', ')', '\n', '*', '{', '}', '?', '+', '|'};
const int operatorsSize = 14;

class SyntaxNode {
private:
    SyntaxNode * parent;
    char value;
    SyntaxNode * left;
    SyntaxNode * right;
public:
    SyntaxNode(char value);
    ~SyntaxNode();
    char getValue();
    SyntaxNode * getParent();
    SyntaxNode * getLeft();
    SyntaxNode * getRight();
    void setParent(SyntaxNode * parent);
    void setLeft(SyntaxNode * left);
    void setRight(SyntaxNode * right);
    bool isOperator() const;
    int operatorPrecedence(char op) const;
};

#endif
