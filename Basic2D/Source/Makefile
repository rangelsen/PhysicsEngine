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

clean:
	rm *.o $(TARGET) $(INC_PATH)/*.h.gch