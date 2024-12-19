#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <cctype>

#ifndef syntax_node_hpp
#define syntax_node_hpp

class SyntaxNode {
public:
    SyntaxNode * parent;
    char value;
    SyntaxNode * left;
    SyntaxNode * right;

    SyntaxNode(char value);
    ~SyntaxNode();

    bool isOperator() const;
    int operatorPrecedence(char op) const;
};

#endif


#ifndef TREE_HPP
#define TREE_HPP

class SyntaxTree {
public:
    SyntaxNode * root;

    SyntaxTree();
    ~SyntaxTree();

    void buildTree(std::string regex);
};

#endif

#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

class Automato {
protected:
    SyntaxTree * syntaxTree;

    std::set<int> startStates;
    std::set<char> alphabet;
    std::map<std::pair<int, char>, std::set<int>> transitions;
    std::set<int> endStates;
public:
    virtual void build(std::string regex) = 0;

    Automato();
    virtual ~Automato();

    virtual void addTransition(int from, int to, char symbol) = 0;
    virtual void setStartState(int state) = 0;
    virtual void setEndState(int state) = 0;

    virtual std::set<int> getStartStates() const = 0;
    virtual std::set<char> getAlphabet() const = 0;
    virtual std::map<std::pair<int, char>, std::set<int>> getTransitions() const = 0;
    virtual std::set<int> getEndStates() const = 0;

    virtual std::vector<int> getNextState(int state, char symbol) const = 0;
};

#endif


#ifndef nfa_hpp
#define nfa_hpp

class NFA : public Automato {
public:
    NFA();
    ~NFA();

    void build(std::string regex) override;

    void addTransition(int from, int to, char symbol) override;
    void setStartState(int state) override;
    void setEndState(int state) override;

    std::set<int> getStartStates() const override;
    std::set<char> getAlphabet() const override;
    std::map<std::pair<int, char>, std::set<int>> getTransitions() const override;
    std::set<int> getEndStates() const override;

    std::vector<int> getNextState(int state, char symbol) const override;
};

#endif


#ifndef dfa_hpp
#define dfa_hpp

class DFA : public NFA {
public:
    DFA(NFA nfa);
    ~DFA();
};

#endif


#ifndef regex_hpp
#define regex_hpp

class Regex {
private:
    NFA * nfa;
public:
    Regex(std::string regex);
    ~Regex();

    bool matches(const std::string& input);
    std::pair<int, int> find(const std::string& input);
    std::vector<std::pair<int, int>> matchAll(const std::string& input);
    std::string replace(const std::string& input, const std::string& replacement);
    bool isMatch(const std::string& input);
};

#endif
