.PHONY: all
all: main.o

CXXFLAGS = -std=c++20 -O3 -Iboost/include -Iac-library

%.o: %.cpp
	g++ $^ $(CXXFLAGS) -o $@

.PHONY: clean_sequence_cases
clean_sequence_cases:
	cp /dev/null samples/in1.txt
	cp /dev/null samples/in2.txt
	cp /dev/null samples/in3.txt
	cp /dev/null samples/in4.txt
	cp /dev/null samples/in5.txt
	cp /dev/null samples/out1.txt
	cp /dev/null samples/out2.txt
	cp /dev/null samples/out3.txt
	cp /dev/null samples/out4.txt
	cp /dev/null samples/out5.txt

.PHONY: clean
clean:
	rm -f *.o
	$(MAKE) clean_sequence_cases
