#ifndef TREE_HPP
#define TREE_HPP

#include "syntax_node.hpp"

class SyntaxTree {
public:
    SyntaxNode * root;

    SyntaxTree(std::string regex);
    ~SyntaxTree();

    SyntaxNode * fromRegex(std::string regex);
};

#endif
