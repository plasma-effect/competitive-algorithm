SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
CXXFLAGS = -std=c++20 -O3 -Iboost/include

$(OBJ): $(SRC)
	g++ $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm *.o
