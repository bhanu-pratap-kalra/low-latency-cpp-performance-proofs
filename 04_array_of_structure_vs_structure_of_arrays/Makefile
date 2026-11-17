CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

TARGETS = ArrayOfStructure StructureOfArrays

.PHONY: all clean

all: $(TARGETS)

ArrayOfStructure: ArrayOfStructure.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

StructureOfArrays: StructureOfArrays.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(RM) $(TARGETS)
