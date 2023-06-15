#include "syntax_tree.hpp"

SyntaxNode* SyntaxTree::getRoot() {
    return this->root;
}

void SyntaxTree::insert(SyntaxNode * node) {
    if (this->root == nullptr) {
        this->root = node;
    } else {
        std::stack<SyntaxNode*> nodeStack;
        nodeStack.push(this->root);

        while(!nodeStack.empty()) {
            SyntaxNode * currentNode = nodeStack.top();
            nodeStack.pop();

            if(currentNode->isOperator()) {
                int currentPrecedence = currentNode->operatorPrecedence(currentNode->getValue());
                int newPrecedence = node->operatorPrecedence(node->getValue());

                if(newPrecedence < currentPrecedence) {
                    SyntaxNode * newParentNode = new SyntaxNode(currentNode->getValue());
                    newParentNode->setLeft(currentNode->getLeft());
                    newParentNode->setRight(node);
                    currentNode->setLeft(newParentNode);
                    break;
                }
            }

            if(currentNode->getLeft() == nullptr) {
                currentNode->setLeft(node);
                break;
            } else if(currentNode->getRight() == nullptr) {
                currentNode->setRight(node);
            } else {
                nodeStack.push(currentNode->getLeft());
                nodeStack.push(currentNode->getRight());
            }
        }
    }
}

SyntaxNode* SyntaxTree::build(std::string expression) {
    for (std::string::size_type i=0; i<expression.length(); i++) {
        char token = expression[i];
        this->insert(new SyntaxNode(token));
    }
    return this->root;
}

std::vector<SyntaxNode*> SyntaxTree::traverse() {
    std::vector<SyntaxNode*> nodes;
    this->traverse(this->root, nodes);
    return nodes;
}

std::vector<SyntaxNode*> SyntaxTree::traverse(SyntaxNode * node, std::vector<SyntaxNode*> & nodes) {
    if (node != nullptr) {
        this->traverse(node->getLeft(), nodes);
        nodes.push_back(node);
        this->traverse(node->getRight(), nodes);
    }
    return nodes;
}
