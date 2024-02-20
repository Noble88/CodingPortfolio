CXX = g++
SRC_DIRS = . $(shell find . -type d)
PROJECT_NAME = $(notdir $(CURDIR))
SOURCES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(PROJECT_NAME)_Executable

$(PROJECT_NAME)_Executable: $(OBJECTS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	@rm -f $(PROJECT_NAME)_Executable $(OBJECTS)
