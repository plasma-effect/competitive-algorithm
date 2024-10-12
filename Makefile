.PHONY: all
all: main.o

CXXFLAGS = -std=c++20 -O3 -Iboost/include -Iac-library

%.o: %.cpp
	g++ $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -f *.o
	./clean_sequence_cases.sh
