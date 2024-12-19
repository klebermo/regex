#ifndef TREE_HPP
#define TREE_HPP

#include "syntax_node.hpp"

class SyntaxTree {
public:
    SyntaxNode * root;

    SyntaxTree();
    ~SyntaxTree();
    
    void buildTree(std::string regex);
};

#endif
