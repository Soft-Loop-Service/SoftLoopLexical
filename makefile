
FLD_SRC = ./src
BIN_SRC = ./bin
SRCS_SRC = $(wildcard $(FLD_SRC)/*/*.cpp) $(wildcard $(FLD_SRC)/*/*/*.cpp) $(wildcard $(FLD_SRC)/*/*/*/*.cpp) $(wildcard $(FLD_SRC)/*/*/*/*/*.cpp)
ANALYSIS_SRC = ./src/analysis.cpp $(SRCS_SRC)

FILES = ""

define MAKEOBJ
   @echo $(subst cpp,o,$(1)) 
   g++ -std=c++2a -c $(1) -o ./bin/$(notdir $(subst cpp,o,$(1)) )

endef



.PHONY: all
all:
	@echo "$(SRCS_SRC)"
	$(foreach filename,$(SRCS_SRC),$(call F,$(filename)))

buildayO:
	@echo "$(ANALYSIS_SRC)"
	rm -f $(wildcard $(BIN_SRC)/*.o)
	$(foreach filename,$(ANALYSIS_SRC),$(call MAKEOBJ,$(filename)))
	g++ -o analysis.out $(wildcard $(BIN_SRC)/*.o)


buildayout:
	@echo "$(ANALYSIS_SRC)"
	g++ -std=c++2a -c $(ANALYSIS_SRC)


	

	
	
