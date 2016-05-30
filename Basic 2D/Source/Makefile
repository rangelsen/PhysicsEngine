CXX = g++

physics_engine: main.o
	$(CXX) main.o -o $@

main.o: main.cpp
	$(CXX) -c main.cpp

clean:
	del *.o physics_engine.exe