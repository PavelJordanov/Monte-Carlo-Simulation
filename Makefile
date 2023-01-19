CC=cc
CXX=g++
CCFLAGS= -g -std=c++11 -Wall -Werror
LDLIBS= -lm
all: Monte_Carlo 
%.o : %.cpp
	$(CXX) -c $(CCFLAGS) $<

Monte_Carlo: Monte_Carlo.o 
	$(CXX) -o Monte_Carlo Monte_Carlo.o  $(CCFLAGS) $(LDLIBS)


clean:
	rm -f core *.o Monte_Carlo

