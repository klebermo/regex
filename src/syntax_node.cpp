#include "syntax_node.hpp"

int precedence(char op) {
    int result = 0;
    for(int i=0; i<operatorsSize; i++) {
        if(op == operators[i]) {
            result = i;
            break;
        }
    }
    return result;
}

bool isOperator(char c) {
    for(int i=0; i<operatorsSize; i++) {
        if(c == operators[i]) return true;
    }
    return false;
}

SyntaxNode::SyntaxNode() {
    value = '\0';
    left = nullptr;
    right = nullptr;
}

SyntaxNode::SyntaxNode(char val) {
    value = val;
    left = nullptr;
    right = nullptr;
}

SyntaxNode::SyntaxNode(char val, SyntaxNode* child) {
    value = val;
    left = child;
    right = nullptr;
}

SyntaxNode::SyntaxNode(char val, SyntaxNode* left, SyntaxNode* right) {
    value = val;
    this->left = left;
    this->right = right;
}

SyntaxNode::~SyntaxNode() {
    delete left;
    delete right;
}

char SyntaxNode::_value() {
    return value;
}

SyntaxNode * SyntaxNode::_left() {
    return left;
}

void SyntaxNode::_left(SyntaxNode * node) {
    left = node;
}

SyntaxNode * SyntaxNode::_right() {
    return right;
}

void SyntaxNode::_right(SyntaxNode * node) {
    right = node;
}

