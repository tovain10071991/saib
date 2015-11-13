# make DEBUG=1

CC = /home/user/Documents/llvm-3.4-build/bin/clang
CXX = /home/user/Documents/llvm-3.4-build/bin/clang++

ELF_INCLUDE := /home/user/Documents/libelf-0.8.13/build/include/
ELF_LIBRARY := /home/user/Documents/libelf-0.8.13/build/lib/

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

INCLUDEDIR := -I$(ELF_INCLUDE)
LIBDIR := -L$(ELF_LIBRARY)

CPPFLAGS += $(INCLUDEDIR)
CXXFLAGS += -c -gstrict-dwarf -g3 -Wall $(INCLUDEDIR) -std=c++11
ifdef DEBUG
	CXXFLAGS += -DDEBUG
endif
LDFLAGS += -lelf

all: $(EXECUTE)

$(EXECUTE): $(OBJECT)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBDIR)

$(SAIB_OBJECT)/%.o: $(SAIB_SOURCE)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm $(EXECUTE) $(OBJECT)
