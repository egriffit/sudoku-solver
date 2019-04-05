CC:=g++
CPPFLAGS:=-std=c++11 -g -Wall

SRCDIR:=src
BUILDDIR:=build
TESTDIR:=test


SOURCES:=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS:=$(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

TEST_MAIN:=$(TESTDIR)/testsMain.cpp
TEST_SOURCES:=$(filter-out $(TEST_MAIN), $(wildcard $(TESTDIR)/*.cpp))
TEST_OBJECT:=$(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o,$(TEST_MAIN))
TESTER:=$(TESTDIR)/tester

all: $(OBJECTS)

#$(OBJECTS): $(SOURCES)
#	$(CC) $(CPPFLAGS) $< -c -o $@


build/Board.o: src/Board.cpp
	$(CC) $(CPPFLAGS) $< -c -o $@

build/SudokuSolver.o: src/SudokuSolver.cpp
	$(CC) $(CPPFLAGS) $< -c -o $@



test: $(TESTER)

$(TESTER): $(TEST_OBJECT) test/testSolver.cpp $(OBJECTS)
	$(CC) $(CPPFLAGS) $^ -o $@

$(TEST_OBJECT): $(TEST_MAIN)
	$(CC) $(CPPFLAGS) $< -c -o $@



help:
	@echo Sources: $(SOURCES)
	@echo Objects: $(OBJECTS)
	@echo Test Main: $(TEST_MAIN)
	@echo Test Sources: $(TEST_SOURCES)
	@echo Test Object: $(TEST_OBJECT)


clean:
	rm build/*.o

