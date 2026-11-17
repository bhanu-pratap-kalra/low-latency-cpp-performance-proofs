CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -Wextra

TARGETS = HotColdTogether HotColdSplit

.PHONY: all clean

all: $(TARGETS)

HotColdTogether: HotColdTogether.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

HotColdSplit: HotColdSplit.cpp Makefile
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -pthread $< $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(RM) $(TARGETS)
