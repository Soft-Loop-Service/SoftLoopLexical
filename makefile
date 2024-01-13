build:
	g++ -o ./main.out ./src/main.cpp  -std=c++2a

buildtable:
	g++ -o ./table.out ./src/table.cpp  -std=c++2a

builday:
	g++ -v -o ./analysis.out ./src/analysis.cpp  -std=c++2a

bnf:
	g++ -o ./BNF_TEST.exe ./src/BNF/BNF_TEST.cpp

bnfa:
	g++ -o ./BNF_TEST.out ./src/BNF/BNF_TEST.cpp  -std=c++20

bnfa2:
	g++ -o ./BNF_TEST.out ./src/BNF/BNF_TEST.cpp  -std=c++2a