#ifndef syntax_node_hpp
#define syntax_node_hpp

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <stdexcept>

const char operators[] = {'^', '.', '[', ']', '$', '(', ')', '\n', '*', '{', '}', '?', '+', '|'};
const int operatorsSize = 14;

class SyntaxNode {
public:
    char value;
    SyntaxNode * left;
    SyntaxNode * right;

    int minRepetitions;
    int maxRepetitions;

    // Construtor para nó literal
    SyntaxNode(char val) 
        : value(val), left(nullptr), right(nullptr) {}

    // Construtor para operadores unários (KleeneStar)
    SyntaxNode(char val, SyntaxNode* child) 
        : value(val), left(child), right(nullptr) {}

    // Construtor para operadores binários (Union, Concatenation)
    SyntaxNode(char val, SyntaxNode* left, SyntaxNode* right) 
        : value(val), left(left), right(right) {}
    
    // Construtor para repetição {n,m}
    SyntaxNode(char val, int minRep, int maxRep, SyntaxNode* child)
        : value(val), left(child), right(nullptr), 
          minRepetitions(minRep), maxRepetitions(maxRep) {}
    
    ~SyntaxNode() {
        delete left;
        delete right;
    }

    bool isOperator() const;
    int operatorPrecedence(char op) const;
};

#endif
