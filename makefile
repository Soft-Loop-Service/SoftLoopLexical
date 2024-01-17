
FLD_SRC = ./src
BIN_SRC = ./bin
SRCS_SRC = $(wildcard $(FLD_SRC)/*/*.cpp) $(wildcard $(FLD_SRC)/*/*/*.cpp) $(wildcard $(FLD_SRC)/*/*/*/*.cpp) $(wildcard $(FLD_SRC)/*/*/*/*/*.cpp)
ANALYSIS_SRC = ./src/analysis.cpp $(SRCS_SRC)

FILES = ""

define MAKEOBJ
   @echo $(subst cpp,o,$(1)) 
   g++ -std=c++20 -c $(1) -o ./bin/$(notdir $(subst cpp,o,$(1)) )


   $(foreach filename,$(ANALYSIS_SRC),$(call MAKEOBJ,$(filename)))

endef

 
builday:
	@echo "$(ANALYSIS_SRC)"
	rm -f $(wildcard $(BIN_SRC)/*.o)
	g++ -std=c++2a -o hoge $(wildcard $(ANALYSIS_SRC))



	
