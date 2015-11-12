CC = /home/user/Documents/llvm-3.4-build/bin/clang
CXX = /home/user/Documents/llvm-3.4-build/bin/clang++

PROJECT_ROOT := .
SAIB_INCLUDE := $(PROJECT_ROOT)/include
SAIB_SOURCE := $(PROJECT_ROOT)/src
SAIB_BIN := $(PROJECT_ROOT)/bin
SAIB_OBJECT := $(PROJECT_ROOT)/object

EXECUTE := $(SAIB_BIN)/saib
SOURCE := $(wildcard $(SAIB_SOURCE)/*.cpp)
SOURCE_BASE_NAME = $(notdir $(SOURCE))
OBJECT_BASE_NAME := $(SOURCE_BASE_NAME:.cpp=.o)
OBJECT := $(foreach n,$(OBJECT_BASE_NAME),$(SAIB_OBJECT)/$(n))

all: $(EXECUTE)

$(EXECUTE): $(OBJECT)
	$(CXX) -o $@ $^

$(SAIB_OBJECT)/%.o: $(SAIB_SOURCE)/%.cpp
	$(CXX) -c -o $@ $<

clean:
	rm $(EXECUTE) $(OBJECT)
