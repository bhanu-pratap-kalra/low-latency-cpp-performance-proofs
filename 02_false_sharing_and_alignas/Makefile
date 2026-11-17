CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

TARGETS = SimpleNoAlignmentExample SimpleAlignas64Example SimpleAlignasExampleHDIS

.PHONY: all clean

all: $(TARGETS)

SimpleNoAlignmentExample: SimpleNoAlignmentExample.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

SimpleAlignas64Example: SimpleAlignas64Example.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

SimpleAlignasExampleHDIS: SimpleAlignasExampleHDIS.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(RM) $(TARGETS)
