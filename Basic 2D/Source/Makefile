CXX = g++

INCLUDE_PATH = C:\Users\Roy Angelsen\Documents\Programmering\PhysicsEngine\Basic 2D\Include
SOURCE_PATH = C:\Users\Roy Angelsen\Documents\Programmering\PhysicsEngine\Basic 2D\Source

CFLAGS = -I "$(INCLUDE_PATH)"

physics_engine: main.o World.o PhysicsSolver.o Object.o
	$(CXX) main.o World.o PhysicsSolver.o Object.o $(CFLAGS) -o $@

main.o: main.cpp
	$(CXX) -c $(CFLAGS) main.cpp

PhysicsSolver.o: PhysicsSolver.cpp "$(INCLUDE_PATH)\PhysicsSolver.h"
	$(CXX) -c $(CFLAGS) PhysicsSolver.cpp

World.o: World.cpp "$(INCLUDE_PATH)\World.h"
	$(CXX) -c $(CFLAGS) World.cpp

Object.o: Object.cpp "$(INCLUDE_PATH)\Object.h"
	$(CXX) -c $(CFLAGS) Object.cpp

clean:
	del *.o physics_engine.exe