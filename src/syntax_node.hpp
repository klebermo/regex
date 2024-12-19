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

const char operators[] = {'[', ']', '.', '^', '$', '(', ')', '*', '+', '?', '{', '}', '|'};
const int operatorsSize = 14;

class SyntaxNode {
public:
    char value = '\0';
    int minRepetitions = 0;
    int maxRepetitions = 0;
    SyntaxNode * left;
    SyntaxNode * right;

    // Construtor para nó literal
    SyntaxNode(char val) : value(val), left(nullptr), right(nullptr) {}

    // Construtor para operadores unários (KleeneStar)
    SyntaxNode(SyntaxNode* child) : left(child), right(nullptr) {}

    // Construtor para operadores binários (Union, Concatenation)
    SyntaxNode(SyntaxNode* left, SyntaxNode* right) : left(left), right(right) {}
    
    // Construtor para repetição {n,m}
    SyntaxNode(int minRep, int maxRep, SyntaxNode* child) : left(child), right(nullptr), minRepetitions(minRep), maxRepetitions(maxRep) {}
    
    ~SyntaxNode() {
        delete left;
        delete right;
    }

    bool isOperator() const;
    int operatorPrecedence(char op) const;
};

#endif
