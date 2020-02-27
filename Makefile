CXX = g++
CXXFLAGS = -Wall -std=c++11 

OBJECTS = mindgame.o

mindgame: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o mindgame mindgame.o
	
mindgame.o: mindgame.cpp
	$(CXX) -g $(CXXFLAGS) -c mindgame.cpp

clean: 
	rm -f *.o
	rm mindgame
