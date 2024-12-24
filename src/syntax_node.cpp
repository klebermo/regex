#include "syntax_node.hpp"

SyntaxNode::SyntaxNode() {
    value = '\0';
    minRepetitions = 0;
    maxRepetitions = 0;
    left = nullptr;
    right = nullptr;
}

SyntaxNode::SyntaxNode(char val) {
    value = val;
    minRepetitions = 0;
    maxRepetitions = 0;
    left = nullptr;
    right = nullptr;
}

SyntaxNode::SyntaxNode(char val, SyntaxNode* child) {
    value = val;
    minRepetitions = 0;
    maxRepetitions = 0;
    left = child;
    right = nullptr;
}

SyntaxNode::SyntaxNode(char val, SyntaxNode* left, SyntaxNode* right) {
    value = val;
    minRepetitions = 0;
    maxRepetitions = 0;
    this->left = left;
    this->right = right;
}

SyntaxNode::SyntaxNode(char val, int minRep, int maxRep, SyntaxNode* child) {
    value = val;
    minRepetitions = minRep;
    maxRepetitions = maxRep;
    left = child;
    right = nullptr;
}

SyntaxNode::~SyntaxNode() {
    delete left;
    delete right;
}

char SyntaxNode::_value() {
    return value;
}

int SyntaxNode::_minRepetitions() {
    return minRepetitions;
}

int SyntaxNode::_maxRepetitions() {
    return maxRepetitions;
}

SyntaxNode * SyntaxNode::_left() {
    return left;
}

SyntaxNode * SyntaxNode::_right() {
    return right;
}

bool SyntaxNode::isOperator() const {
    for(int i = 0; i < operatorsSize; i++)
        if(this->value == operators[i]) return true;
    return false;
}

int SyntaxNode::precedence(char op) const {
    int result = 0;
    for(int i=0; i<operatorsSize; i++) {
        if(op == operators[i]) {
            result = i;
            break;
        }
    }
    return result;
}
