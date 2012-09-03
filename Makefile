CXX = clang++
CXXFLAGS = -std=c++11
LDFLAGS = -lglut

objects = main.o lsystem.o gl_renderer.o

all:	$(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o lsystem 

clean:
	rm -f $(objects)
	rm -f lsystem

