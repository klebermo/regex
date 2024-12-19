#include "syntax_node.hpp"

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
