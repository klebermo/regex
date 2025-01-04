#include "syntax_tree.hpp"

SyntaxTree::SyntaxTree(std::string regex) {
    root = fromRegex(regex);
}

SyntaxTree::~SyntaxTree() {
    delete root;
}

SyntaxNode * SyntaxTree::getRoot() {
    return root;
}

void SyntaxTree::print() {
    if(root == nullptr) {
        std::cout << "_" << std::endl;
        return;
    }

    std::cout << root->_value() << std::endl;
    print(root->_left(), 1);
    print(root->_right(), 1);
}

void SyntaxTree::print(SyntaxNode * node, int level) {
    if(node == nullptr) {
        for(int i=0; i<level; i++) std::cout << "\t";
        std::cout << '_' << std::endl;
        return;
    }

    for(int i=0; i<level; i++) std::cout << "\t";
    std::cout << node->_value() << std::endl;
    print(node->_left(), level+1);
    print(node->_right(), level+1);
}

SyntaxNode * SyntaxTree::fromRegex(std::string regex) {
    std::stack<SyntaxNode*> operands;

    for (size_t i = 0; i < regex.size(); i++) {
        char c = regex[i];

        switch(c) {
            case '[':
                {
                    operands.push(new SyntaxNode('['));
                    break;
                }
            case ']':
                {
                    std::string charset;
                    while(operands.top()->_value() != '[') {
                        charset += operands.top()->_value();
                        operands.pop();
                    }
                    operands.push(new SyntaxNode('[', fromRegex(charset), nullptr));
                    break;
                }
            case '.':
                {
                    if(operands.empty()) {
                        operands.push(new SyntaxNode('.'));
                        break;
                    } else {
                        SyntaxNode * node = operands.top(); operands.pop();
                        operands.push(new SyntaxNode('.', node, nullptr));
                        break;
                    }
                }
            case '^':
                {
                    operands.push(new SyntaxNode('^'));
                    break;
                }
            case '$':
                {
                    operands.push(new SyntaxNode('$'));
                    break;
                }
            case '(':
                {
                    operands.push(new SyntaxNode('('));
                    break;
                }
            case ')':
                {
                    std::string charset;
                    while(operands.top()->_value() != '(') {
                        charset += operands.top()->_value();
                        operands.pop();
                    }
                    operands.push(new SyntaxNode('(', fromRegex(charset)));
                    break;
                }
            case '*':
                {
                    operands.push(new SyntaxNode('*'));
                    break;
                }                
            case '+':
                {
                    operands.push(new SyntaxNode('+'));
                    break;
                }
            case '?':
                {
                    operands.push(new SyntaxNode('?'));
                    break;
                }
            case '{':
                {
                    operands.push(new SyntaxNode('{'));
                    break;
                }
            case '}':
                {
                    std::string min, max;
                    while(operands.top()->_value() != '{') {
                        while(isalnum(operands.top()->_value())) {
                            max += operands.top()->_value();
                            operands.pop();
                        }
                        min += operands.top()->_value();
                        operands.pop();
                    }
                    auto left = new SyntaxNode(stoi(min));
                    auto right = new SyntaxNode(stoi(max));
                    operands.push(new SyntaxNode('{', left, right));
                    break;
                }
            case '|':
                {
                    SyntaxNode * left = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('|', left, nullptr));
                    break;
                }
            default:
                {
                    if(operands.empty()) {
                        operands.push(new SyntaxNode(c));
                        break;
                    } else {
                        SyntaxNode * node = operands.top(); operands.pop();
                        SyntaxNode * child = new SyntaxNode(node->_value());
                        if(node->_left() == nullptr) {
                            child->_left(new SyntaxNode(c));
                        } else {
                            child->_right(new SyntaxNode(c));
                        }
                        operands.push(child);
                        break;
                    }
                }
        }
    }

    while(operands.size() > 1) {
        SyntaxNode * right = operands.top(); operands.pop();
        SyntaxNode * left = operands.top(); operands.pop();
        operands.push(new SyntaxNode('.', left, right));
    }

    return operands.top();
}
