#include "syntax_tree.hpp"

SyntaxTree::SyntaxTree() {
    this->root = nullptr;
}

SyntaxTree::~SyntaxTree() {
    delete this->root;
}

void SyntaxTree::buildTree(std::string regex) {
    std::stack<SyntaxNode*> operators;
    std::stack<SyntaxNode*> operands;

    auto precedence = [](char op) -> int {
        switch(op) {
            case '|':
                return 3;
            case '.':
                return 2;
            case '*': case '?' : case '+':
                return 1;
            case '(':
                return 0;
            default:
                return -1;
        }
    };

    auto applyOperator = [&]() {
        if (operators.empty() || operands.empty()) return;
        char op = operators.top()->value;
        operators.pop();

        if (op == '|') { // Union
            SyntaxNode* right = operands.top(); operands.pop();
            SyntaxNode* left = operands.top(); operands.pop();
            SyntaxNode* unionNode = new SyntaxNode(op, left, right);
            operands.push(unionNode);
        } else if (op == '.') { // Concatenation
            SyntaxNode* right = operands.top(); operands.pop();
            SyntaxNode* left = operands.top(); operands.pop();
            SyntaxNode* concatNode = new SyntaxNode(op, left, right);
            operands.push(concatNode);
        } else if (op == '*' || op == '+' || op == '?') { // Unary Operators
            SyntaxNode* operand = operands.top(); operands.pop();
            SyntaxNode* repeatNode = new SyntaxNode(op, operand, nullptr);
            operands.push(repeatNode);
        }
    };

    for (size_t i = 0; i < regex.length(); ++i) {
        char c = regex[i];

        if (std::isalnum(c) || c == '\n' || c == '^' || c == '$') {
            operands.push(new SyntaxNode(c));
        } else if (c == '(') {
            operators.push(new SyntaxNode(c));
        } else if (c == ')') {
            while (!operators.empty() && operators.top()->value != '(') {
                applyOperator();
            }
            if (!operators.empty()) operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()->value) >= precedence(c)) {
                applyOperator();
            }
            operators.push(new SyntaxNode(c));
        }
    }

    while (!operators.empty()) {
        applyOperator();
    }

    this->root = operands.top();
}