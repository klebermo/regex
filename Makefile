export cc := g++
export cpp_flags := -Wall -pedantic -fPIC -g

all: regex

regex: syntaxNode.o syntaxTree.o automato.o transition.o regex.o
	$(cc) -shared -o libregex.so syntaxNode.o syntaxTree.o automato.o transition.o regex.o
	ar rcs libregex.a syntaxNode.o syntaxTree.o automato.o transition.o regex.o

syntaxNode.o: src/syntax_node.cpp
	$(cc) $(cpp_flags) -c src/syntax_node.cpp -o syntaxNode.o

syntaxTree.o: src/syntax_tree.cpp
	$(cc) $(cpp_flags) -c src/syntax_tree.cpp -o syntaxTree.o

automato.o: src/automato.cpp
	$(cc) $(cpp_flags) -c src/automato.cpp -o automato.o

transition.o: src/transition.cpp
	$(cc) $(cpp_flags) -c src/transition.cpp -o transition.o

regex.o: src/regex.cpp
	$(cc) $(cpp_flags) -c src/regex.cpp -o regex.o

clean:
	rm -f *.o *.so
