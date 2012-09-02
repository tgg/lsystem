CXX = clang++
CXXFLAGS = -std=c++11
LDFLAGS =

objects = main.o lsystem.o

all:	$(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o lsystem 

clean:
	@rm -f $(objects)
	@rm -f lsystem

