#include "syntax_node.hpp"

SyntaxNode::SyntaxNode(char value) {
    this->parent = nullptr;
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}

SyntaxNode::~SyntaxNode() {
    delete this->parent;
    delete this->left;
    delete this->right;
}

char SyntaxNode::getValue() {
    return this->value;
}

SyntaxNode * SyntaxNode::getParent() {
    return this->parent;
}

SyntaxNode * SyntaxNode::getLeft() {
    return this->left;
}

SyntaxNode * SyntaxNode::getRight() {
    return this->right;
}

void SyntaxNode::setParent(SyntaxNode * parent) {
    this->parent = parent;
}

void SyntaxNode::setLeft(SyntaxNode * left) {
    this->left = left;
}

void SyntaxNode::setRight(SyntaxNode * right) {
    this->right = right;
}

bool SyntaxNode::isOperator() const {
    for(int i = 0; i < operatorsSize; i++)
        if(this->value == operators[i]) return true;
    return false;
}

int SyntaxNode::operatorPrecedence(char op) const {
    int result = 0;
    for(int i=0; i<operatorsSize; i++) {
        if(op == operators[i]) {
            result = i;
            break;
        }
    }
    return result;
}
