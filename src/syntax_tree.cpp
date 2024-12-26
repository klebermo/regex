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
    if(root == nullptr) return;

    std::stack<SyntaxNode*> stack;
    SyntaxNode* current = root;

    while(current != nullptr || !stack.empty()) {
        while(current != nullptr) {
            stack.push(current);
            current = current->_left();
        }

        current = stack.top();
        stack.pop();

        std::cout << current->_value() << " ";
        current = current->_right();
    }
}

SyntaxNode * SyntaxTree::fromRegex(std::string regex) {
    std::stack<SyntaxNode*> operands;

    for (size_t i = 0; i < regex.size(); i++) {
        char c = regex[i];

        switch(c) {
            case ']':
                {
                    std::string charset;
                    while(!operands.empty() && operands.top()->_value() != '[') {
                        auto op = operands.top(); operands.pop();
                        if(op->_value() != '[' && op->_value() != ']') charset += op->_value();
                    }
                    operands.push(new SyntaxNode('[', fromRegex(charset), nullptr));
                    break;
                }
            case '.':
                {
                    SyntaxNode * node = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('.', node, nullptr));
                    break;
                }
            case '^':
                {
                    SyntaxNode * node = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('^', node, nullptr));                    
                    break;
                }
            case '$':
                {
                    SyntaxNode * node = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('$', node, nullptr));
                    break;
                }                
            case ')':
                {
                    std::string charset;
                    while(!operands.empty() && operands.top()->_value() != '(') {
                        auto op = operands.top(); operands.pop();
                        if(op->_value() != '(' && op->_value() != ')') charset += op->_value();
                    }
                    operands.push(new SyntaxNode('(', fromRegex(charset), nullptr));
                    break;
                }
            case '*':
                {
                    SyntaxNode * node = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('*', node, nullptr));
                    break;
                }                
            case '+':
                {
                    SyntaxNode * node = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('+', node, nullptr));
                    break;
                }
            case '?':
                {
                    SyntaxNode * node = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('?', node, nullptr));
                    break;
                }                
            case '}':
                {
                    std::string min, max;
                    while(!operands.empty() && operands.top()->_value() != '{') {
                        auto op = operands.top(); operands.pop();
                        while(op->_value() != '{' && op->_value() != '}' && isalnum(op->_value())) {
                            max += op->_value();
                            op = operands.top(); operands.pop();
                        }
                        if(isalnum(op->_value())) min += op->_value();
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
                    operands.push(new SyntaxNode(c));
                    break;
                }
        }

        while(operands.size()>1) {
            auto left = operands.top(); operands.pop();
            auto right = operands.top(); operands.pop();
            auto node = new SyntaxNode('.', left, right);
            operands.push(node);
        }
    }

    return operands.top();
}
