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

SyntaxNode * SyntaxTree::fromRegex(std::string regex) {
    SyntaxNode * node = nullptr;

    std::stack<char> operators;
    std::stack<SyntaxNode*> operands;

    std::string charset = "";
    SyntaxNode * temp = new SyntaxNode();

    for (size_t i = 0; i < regex.size(); ++i) {
        char c = regex[i];

        switch(c) {
            case '(':
                operators.push(c);
                break;
            case ')':
                while (!operators.empty() && operators.top() != '(') {
                    SyntaxNode * right = operands.top(); operands.pop();
                    SyntaxNode * left = operands.top(); operands.pop();
                    char op = operators.top(); operators.pop();
                    operands.push(new SyntaxNode(op, left, right));
                }
                if(!operators.empty() && operators.top() == '(') operators.pop();
                break;
            case '[':
                operators.push(c);
                break;
            case ']':
                while (!operators.empty() && operators.top() != '[') {
                    charset += operators.top();
                    operators.pop();
                }
                if(!operators.empty() && operators.top() == '[') operators.pop();
                for(std::string::size_type i=0; i<charset.size(); i++) {
                    SyntaxNode * right = new SyntaxNode(charset.at(i));
                    SyntaxNode * left = new SyntaxNode(charset.at(++i));
                    SyntaxNode * node = new SyntaxNode('.', left, right);
                    operands.push(node);
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
                while(!operators.empty() && temp->precedence(operators.top()) >= temp->precedence(c)) {
                    SyntaxNode * right = operands.top(); operands.pop();
                    SyntaxNode * left = operands.top(); operands.pop();
                    char op = operators.top(); operators.pop();
                    operands.push(new SyntaxNode(op, left, right));
                }
                operators.push('|');
                break;
            case '*':
                if(!operands.empty()) {
                    SyntaxNode * child = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('*', child));
                }
                break;
            case '+':
                if(!operands.empty()) {
                    SyntaxNode * child = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('+', child));
                }
                break;
            case '?':
                if(!operands.empty()) {
                    SyntaxNode * child = operands.top(); operands.pop();
                    operands.push(new SyntaxNode('?', child));
                }
                break;
            case '.':
                while(!operators.empty() && temp->precedence(operators.top()) >= temp->precedence(c)) {
                    SyntaxNode * right = operands.top(); operands.pop();
                    SyntaxNode * left = operands.top(); operands.pop();
                    char op = operators.top(); operators.pop();
                    operands.push(new SyntaxNode(op, left, right));
                }
                operators.push('.');
                break;
            case '^':
                operands.push(new SyntaxNode('^'));
                break;
            case '$':
                operands.push(new SyntaxNode('$'));
                break;
            case '-':
                operators.push('-');
                break;
            default:
                operands.push(new SyntaxNode(c));
                break;
        }
    }

    while(!operators.empty()) {
        SyntaxNode * right = operands.top(); operands.pop();
        SyntaxNode * left = operands.top(); operands.pop();
        char op = operators.top(); operators.pop();
        operands.push(new SyntaxNode(op, left, right));
    }

    if(!operands.empty()) {
        node = operands.top();
    }

    return node;
}
