CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic
LDFLAGS = -lglut

OBJECTS = main.o lsystem.o gl_renderer.o

all:	$(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o lsystem 

clean:
	rm -f $(OBJECTS)
	rm -f lsystem

