CXX = g++
SRC_DIR = .
PROJECT_NAME = $(notdir $(CURDIR))
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(PROJECT_NAME)_Executable

$(PROJECT_NAME)_Executable: $(OBJECTS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	@rm -f $(PROJECT_NAME)_Executable $(OBJECTS)
