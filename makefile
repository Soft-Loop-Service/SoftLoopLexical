build:
	g++ -o ./bin/main.exe ./src/main.cpp

bnf:
	g++ -o ./BNF_TEST.exe ./src/BNF/BNF_TEST.cpp

bnfa:
	g++ -o ./BNF_TEST.out ./src/BNF/BNF_TEST.cpp  -std=c++20

bnfa2:
	g++ -o ./BNF_TEST.out ./src/BNF/BNF_TEST.cpp  -std=c++2a