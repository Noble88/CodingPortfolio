CXX = g++
SRC_DIRS = . $(shell find . -type d)
PROJECT_NAME = $(notdir $(CURDIR))
SOURCES := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)
MODIFIED_SOURCES := $(shell git status --porcelain | grep -E '\.cpp' | cut -c 4-)

.PHONY: all clean

all: $(PROJECT_NAME)_Executable

$(PROJECT_NAME)_Executable: $(OBJECTS)
ifeq ($(strip $(MODIFIED_SOURCES)),)
	@echo -n "Building: '$(PROJECT_NAME)'"
	@for ((i = 0; i < 30 - ${#PROJECT_NAME}; i++)); do \
		echo -n " "; \
	done
	@echo "| Nothing to be done for 'all'."
else
	$(CXX) $^ -o $@
endif

%.o: %.cpp
	$(CXX) -c $< -o $@

clean:
	@rm -f $(PROJECT_NAME)_Executable $(OBJECTS)
