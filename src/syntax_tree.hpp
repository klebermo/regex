#ifndef TREE_HPP
#define TREE_HPP

#include "syntax_node.hpp"

class SyntaxTree {
private:
    SyntaxNode * root;
public:
    SyntaxTree(std::string regex);
    ~SyntaxTree();

    SyntaxNode * getRoot();
    SyntaxNode * fromRegex(std::string regex);

    void print();
    void print(SyntaxNode * node, int level);
};

#endif
