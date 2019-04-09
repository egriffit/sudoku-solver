# compiler and compilation flags
CC:=g++
CPPFLAGS:=-std=c++11 -g -Wall

# directory locations
SRCDIR:=src
BUILDDIR:=build
TESTDIR:=test
BINDIR:=bin

# create build and bin directories if they do not exist
$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(BINDIR))

# scrape src directory for sources and convert them to objects
MAINPROG:=$(BINDIR)/sudoku-solver
SOURCES:=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS:=$(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))


TEST_MAIN:=$(TESTDIR)/testsMain.cpp
TEST_SOURCES:=$(filter-out $(TEST_MAIN), $(wildcard $(TESTDIR)/*.cpp))
TEST_OBJECT:=$(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TEST_MAIN))
TESTER:=$(BINDIR)/unitTester


all: $(MAINPROG)

$(MAINPROG): $(OBJECTS)
	$(CC) $(CPPFLAGS) $^ -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) $< -c -o $@
	



tests: $(TESTER)

# remove main object from compilation of tests
$(TESTER): $(TEST_OBJECT) $(TEST_SOURCES) $(filter-out build/SudokuDriver.o, $(OBJECTS))
	$(CC) $(CPPFLAGS) $^ -o $@

$(TEST_OBJECT): $(TEST_MAIN)
	$(CC) $(CPPFLAGS) $< -c -o $@




.PHONY: help
help:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Test Main: $(TEST_MAIN)
	@echo Test Sources: $(TEST_SOURCES)
	@echo Test Object: $(TEST_OBJECT)


.PHONY: clean
clean:
	rm -r build/ bin/

