#ifndef TREE_HPP
#define TREE_HPP

#include "syntax_node.hpp"

#include <string>
#include <vector>
#include <stack>

class SyntaxTree {
private:
    SyntaxNode * root;

    std::vector<SyntaxNode*> traverse(SyntaxNode * node, std::vector<SyntaxNode*> & nodes);
public:
    SyntaxNode * getRoot();
    void insert(SyntaxNode * node);
    SyntaxNode * build(std::string expression);
    std::vector<SyntaxNode*> traverse();
};

#endif
