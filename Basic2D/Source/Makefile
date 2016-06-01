INC_PATH = /home/roy/Documents/Programmering/PhysicsEngine/Basic2D/Include
SRC_PATH = /home/roy/Documents/Programmering/PhysicsEngine/Basic2D/Source

CXXFLAGS = -I $(INC_PATH)

SRC = main.cpp World.cpp PhysicsSolver.cpp Object.cpp

OBJS = $(SRC:.cpp=.o)

TARGET = PhysicsEngine

$(TARGET): $(OBJS)
	$(CXX) $^ $(CXXFLAGS) -o $@

%.o : %.cpp $(INC_PATH)/%.h
	$(CXX) -c $(CXXFLAGS) $^

#main.o: main.cpp
#	$(CXX) -c $(CXXFLAGS) main.cpp

#PhysicsSolver.o: PhysicsSolver.cpp $(INCLUDE_PATH)/PhysicsSolver.h
#	$(CXX) -c $(CXXFLAGS) PhysicsSolver.cpp

#World.o: World.cpp $(INCLUDE_PATH)/World.h
#	$(CXX) -c $(CXXFLAGS) World.cpp

#Object.o: Object.cpp $(INCLUDE_PATH)/Object.h
#	$(CXX) -c $(CXXFLAGS) Object.cpp

clean:
	rm *.o