CXX = g++11
CXXFLAGS = -std=c++11 -g -Wall -I /usr/include/
LIBDIR = /usr/lib/
LNFLAGS = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

EXEC = game
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)

# main target
all: $(OBJECTS)
	$(CXX) -L $(LIBDIR) $(OBJECTS) $(CXXFLAGS) $(LNFLAGS) -o $(EXEC) $(HEADERS)

-include $(OBJECTS:.o:.d)

# obtain object files
%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
	$(CXX) -M $(CXXFLAGS) $*.cc > $*.d

# note: automatic variables
# $< contains the first dependency file name
# $@ contains the target file name

.PHONY: clean
# clean out the directory but keep the executables with command clean
clean: 
	rm -f $(EXEC) *~ *% *# .#* *.o *.d
