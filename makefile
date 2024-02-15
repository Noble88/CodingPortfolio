CXX = g++
SRC_DIR = .
TERMINAL_DIR = TerminalManager
RESOURCES_DIR = Resources
DEBUGGER_DIR = $(RESOURCES_DIR)/Debugger
SOURCES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(TERMINAL_DIR)/*.cpp) $(wildcard $(DEBUGGER_DIR)/*.cpp)
HEADERS := $(wildcard $(SRC_DIR)/*.h) $(wildcard $(TERMINAL_DIR)/*.h) $(wildcard $(DEBUGGER_DIR)/*.h)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: main

main: $(OBJECTS)
	$(CXX) $^ -o $@ -std=c++17 -lstdc++fs

%.o: %.cpp $(HEADERS)
	$(CXX) -c $< -o $@

clean:
	@rm -f main $(OBJECTS)
