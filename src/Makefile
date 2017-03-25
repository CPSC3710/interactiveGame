CXX = g++11
CXXFLAGS = -std=c++11 -Wall -I /usr/include/
LIBDIR = /usr/lib/
LNFLAGS = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm
OBJECTS = object.o robot.o street.o cylinder.o rectangularPrism.o triangularPrism.o coordinate3d.o

game : main.o $(OBJECTS)
	$(CXX) -L $(LIBDIR) -o $@ $^ $(LNFLAGS) 

clean :
	rm -f *.o *~ *% *# .#*

clean-all : clean
	rm -f game 