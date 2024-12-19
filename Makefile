export cc := g++
export cpp_flags := -Wall -pedantic -fPIC -g

all: regex

regex: syntaxNode.o syntaxTree.o automato.o dfa.o nfa.o regex.o
	$(cc) -shared -o libregex.so syntaxNode.o syntaxTree.o automato.o dfa.o nfa.o regex.o
	ar rcs libregex.a syntaxNode.o syntaxTree.o automato.o dfa.o nfa.o regex.o

syntaxNode.o: src/syntax_node.cpp
	$(cc) $(cpp_flags) -c src/syntax_node.cpp -o syntaxNode.o

syntaxTree.o: src/syntax_tree.cpp
	$(cc) $(cpp_flags) -c src/syntax_tree.cpp -o syntaxTree.o

automato.o: src/automato.cpp
	$(cc) $(cpp_flags) -c src/automato.cpp -o automato.o

dfa.o: src/dfa.cpp
	$(cc) $(cpp_flags) -c src/dfa.cpp -o dfa.o

nfa.o: src/nfa.cpp
	$(cc) $(cpp_flags) -c src/nfa.cpp -o nfa.o

regex.o: src/regex.cpp
	$(cc) $(cpp_flags) -c src/regex.cpp -o regex.o

clean:
	rm -f *.o *.so
