.PHONY: default
default: main.o

WARNINGS = -Wall -Wextra -Werror=return-type
INCLUDES = -Iboost/include -Iac-library -Icompetitive-library/include
CXXFLAGS = -std=c++20 -O3  -DLOCAL_DEBUG $(INCLUDES) $(WARNINGS)

%.o: %.cpp
	g++ -MMD -MP $< $(CXXFLAGS) -o $@

-include main.d

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
clean: clean_sequence_cases
	rm -f *.o *.d

.PHONY: reset
reset: clean
	bazel run @competitive_library//expander -- $(PWD)/main.tmp.cpp -o $(PWD)/main.cpp
