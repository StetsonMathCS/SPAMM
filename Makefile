CXX=g++ -Wall -std=c++11 -ltelnet -lhiredis

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

main: $(obj)
	$(CXX) -o $@ $^

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see `man g++` for details on the -MM and -MT options)
%.d: %.cpp
	$(CXX) $< -MM -MT $(@:.d=.o) > $@

.PHONY: clean
clean:
	rm -f $(obj) main

.PHONY: cleandep
cleandep:
	rm -f $(dep)

