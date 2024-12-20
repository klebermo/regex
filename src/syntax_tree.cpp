#include "syntax_tree.hpp"

SyntaxTree::SyntaxTree(std::string regex) {
    root = fromRegex(regex);
}

SyntaxTree::~SyntaxTree() {
    delete root;
}

SyntaxNode * SyntaxTree::fromRegex(std::string regex) {
    SyntaxNode * node = nullptr;

    std::stack<char> operators;
    std::stack<SyntaxNode*> operands;

    for (size_t i = 0; i < regex.size(); ++i) {
        char c = regex[i];

        switch(c) {
            case '(':
                operators.push(c);
                break;
            case ')':
                while (!operators.empty() && operators.top() != '(') {
                    //
                }
                break;
            case '[':
                operators.push(c);
                break;
            case ']':
                while (!operators.empty() && operators.top() != '[') {
                    //
                }
                break;
            case '{':
                operators.push(c);
                break;
            case '}':
                while (!operators.empty() && operators.top() != '{') {
                    //
                }
                break;
            case '|':
                break;
            case '*':
                break;
            case '+':
                break;
            case '?':
                break;
            case '.':
                break;
            case '^':
                break;
            case '$':
                break;
            case '-':
                break;
            default:
                operators.push(c);
                break;
        }
    }

    return node;
}