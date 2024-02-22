CXX = g++
SRC_DIRS = . $(shell find . -type d)
PROJECT_NAME = $(notdir $(CURDIR))
SOURCES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(PROJECT_NAME)_Executable

$(PROJECT_NAME)_Executable: $(OBJECTS)
	@if [ -n "$$(git status --porcelain)" ]; then \
		echo "Building: $(PROJECT_NAME)"; \
		$(CXX) $^ -o $@; \
	else \
		echo "Building: $(PROJECT_NAME)"; \
		echo "| Nothing to be done for 'all'."; \
	fi

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	@rm -f $(PROJECT_NAME)_Executable $(OBJECTS)
