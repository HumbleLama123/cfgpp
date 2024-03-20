CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -O2
SRC = main.cpp cfgpp.cpp
OBJ = $(SRC:.cpp=.o)

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) a.out

.PHONY: all clean