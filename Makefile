CXX       := clang++
CXX_FLAGS := -Wall -Wextra -g -std=c++17
LD_FLAGS  := 

BIN_DIR  	:= bin
SRC_DIR  	:= src

TARGETS 	:= PortRank Dijkstra
SRCS    	:= FlightGraph
SRCS_O  	:= $(addsuffix .o, $(SRCS))

all : $(TARGETS)

clean:
		@echo "🧹 Clearing bin"
		-rm $(BIN_DIR)/*

run:
		@echo "🚀 Running..."
		$(addprefix ./$(BIN_DIR)/, $(TARGETS))
		
$(TARGETS) : $(SRCS_O)
		@echo "🏗 Building $@"
		$(CXX) $(CXX_FLAGS) -c -o $(BIN_DIR)/$@.o $(SRC_DIR)/$@.cpp
		$(CXX) $(CXX_FLAGS) $(LD_FLAGS) -o $(BIN_DIR)/$@ $(BIN_DIR)/$(addsuffix .o, $@) $(addprefix $(BIN_DIR)/, $(SRCS_O))

$(SRCS_O):
		$(CXX) $(CXX_FLAGS) -c -o $(BIN_DIR)/$@ $(SRC_DIR)/$(patsubst %.o,%.cpp, $@)
		
.PHONY: clean run