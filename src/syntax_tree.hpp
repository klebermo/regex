#ifndef TREE_HPP
#define TREE_HPP

#include "syntax_node.hpp"

class SyntaxTree {
    SyntaxNode * root;
public:
    SyntaxTree(std::string regex);
    ~SyntaxTree();

    SyntaxNode * getRoot();
    SyntaxNode * fromRegex(std::string regex);
};

#endif
