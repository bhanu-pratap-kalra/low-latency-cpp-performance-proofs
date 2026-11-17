CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

TARGETS = SequentialAccess StridedAccess

.PHONY: all clean

all: $(TARGETS)

SequentialAccess: SequentialAccess.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

StridedAccess: StridedAccess.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(RM) $(TARGETS)