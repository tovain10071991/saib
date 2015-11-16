# make DEBUG=1

CC = /home/user/Documents/llvm-3.4-build/bin/clang
CXX = /home/user/Documents/llvm-3.4-build/bin/clang++

ELF_INCLUDE := /home/user/Documents/libelf-0.8.13/build/include/
ELF_LIBRARY := /home/user/Documents/libelf-0.8.13/build/lib/

XED_INCLUDE := /home/user/Documents/pin-2.14-71313-gcc.4.4.7-linux/extras/xed-intel64/include/
XED_STATIC := /home/user/Documents/pin-2.14-71313-gcc.4.4.7-linux/extras/xed-intel64/lib/libxed.a

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

INCLUDEDIR := -I$(ELF_INCLUDE) -I$(XED_INCLUDE)
LIBDIR := -L$(ELF_LIBRARY) $(XED_STATIC)

CPPFLAGS += $(INCLUDEDIR)
CXXFLAGS += -c -gstrict-dwarf -g3 $(INCLUDEDIR) -std=c++11# -Wall
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

clean-out:
	rm $(OUTPUT)
