#include "syntax_tree.hpp"

SyntaxTree::SyntaxTree(std::string regex) {
    root = nullptr;

    std::stack<char> operators;
    std::stack<SyntaxNode*> operands;

    for (size_t i = 0; i < regex.size(); ++i) {
        char c = regex[i];

        if (std::isalnum(c)) {
            operands.push(new SyntaxNode(c));
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                //
            }
        } else if (c == '[') {
            operators.push(c);
        } else if (c == ']') {
            while (!operators.empty() && operators.top() != '[') {
                //
            }
        } else if (c == '{') {
            operators.push(c);
        } else if (c == '}') {
            std::string minrepetitions, maxrepetitions;
            while (!operators.empty() && operators.top() != '{') {
                char op = operators.top();
                operators.pop();

                if(op == ',') {
                    maxrepetitions = minrepetitions;
                    minrepetitions = "";
                } else {
                    minrepetitions = op + minrepetitions;
                }
            }

            SyntaxNode * node = new SyntaxNode(std::stoi(minrepetitions), std::stoi(maxrepetitions), operands.top());
            operands.pop();
            operands.push(node);
        } else if (c == '|') {
            //
        } else if (c == '*') {
            //
        } else if (c == '+') {
            //
        } else if (c == '?') {
            //
        } else if (c == '.') {
            //
        } else if (c == '^') {
            //
        } else if (c == '$') {
            //
        } else if ( c == '-') {
            //
        }
    }

    root = operands.top();
}

SyntaxTree::~SyntaxTree() {
    delete root;
}

SyntaxNode * SyntaxTree::getRoot() const {
    return root;
}
