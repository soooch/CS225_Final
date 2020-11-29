CXX       := clang++
CXX_FLAGS := -Wall -Wextra -g -std=c++14
LD_FLAGS  := 

BIN_DIR  	:= bin
SRC_DIR  	:= src

TARGETS 	:= PortRank Dijkstra
SRCS    	:= FlightGraph
SRCS_O  	:= $(addsuffix .o, $(SRCS))
OBJS      := $(addsuffix .o, $(TARGETS)) $(SRCS_O)

all : $(TARGETS)

clean:
		@echo "🧹 Clearing bin"
		-rm $(BIN_DIR)/*

run:
		@echo "🚀 Running..."
		$(addprefix ./$(BIN_DIR)/, $(TARGETS))
		
PortRank : $(SRCS_O) PortRank.o
		@echo "🏗 Building $@"
		$(CXX) $(CXX_FLAGS) $(LD_FLAGS) -o $(BIN_DIR)/$@ $(BIN_DIR)/$(addsuffix .o, $@) $(addprefix $(BIN_DIR)/, $(SRCS_O))

Dijkstra : $(SRCS_O) Dijkstra.o
		@echo "🏗 Building $@"
		$(CXX) $(CXX_FLAGS) $(LD_FLAGS) -o $(BIN_DIR)/$@ $(BIN_DIR)/$(addsuffix .o, $@) $(addprefix $(BIN_DIR)/, $(SRCS_O))

$(OBJS):
		$(CXX) $(CXX_FLAGS) -c -o $(BIN_DIR)/$@ $(SRC_DIR)/$(patsubst %.o,%.cpp, $@)
		
.PHONY: clean run