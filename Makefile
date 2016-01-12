# make DEBUG=1

CC = /home/user/Documents/llvm-3.4-build/bin/clang
CXX = /home/user/Documents/llvm-3.4-build/bin/clang++
LLVM_CONFIG ?= /home/user/Documents/llvm-3.4-build/bin/llvm-config

LLVMLIBS=$(shell $(LLVM_CONFIG) --libs core option bitwriter bitreader irreader linker ipo instrumentation mcparser objcarcopts)

TREE_INCLUDE = /home/user/Documents/tree-3.1/src

PROJECT_ROOT := .
SAIB_INCLUDE := $(PROJECT_ROOT)/include
SAIB_SOURCE := $(PROJECT_ROOT)/src
SAIB_BIN := $(PROJECT_ROOT)/bin
SAIB_OBJECT := $(PROJECT_ROOT)/object
SAIB_OUT := $(PROJECT_ROOT)/out

EXECUTE := $(SAIB_BIN)/saib
SOURCE := $(wildcard $(SAIB_SOURCE)/*.cpp)
SOURCE_BASE_NAME = $(notdir $(SOURCE))
OBJECT_BASE_NAME := $(SOURCE_BASE_NAME:.cpp=.o)
OBJECT := $(foreach n,$(OBJECT_BASE_NAME),$(SAIB_OBJECT)/$(n))
OUTPUT := $(wildcard $(SAIB_OUT)/*out*)

INCLUDEDIR := -I$(TREE_INCLUDE)
LIBDIR := $(LLVMLIBS)

CPPFLAGS += $(INCLUDEDIR) $(shell $(LLVM_CONFIG) --cppflags)
CXXFLAGS += -c -gstrict-dwarf -g3 $(INCLUDEDIR) -std=c++11 $(shell $(LLVM_CONFIG) --cxxflags) -fexceptions
ifdef DEBUG
	CXXFLAGS += -DDEBUG
endif
LDFLAGS += $(shell $(LLVM_CONFIG) --ldflags)

all: $(EXECUTE)

$(EXECUTE): $(OBJECT)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBDIR)

$(SAIB_OBJECT)/%.o: $(SAIB_SOURCE)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm $(EXECUTE) $(OBJECT)

clean-out:
	rm $(OUTPUT)
