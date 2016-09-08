INCLUDEDIR = /home/roy/Documents/Programmering/PhysicsEngine/Basic2D/Include
SOURCEDIR = /home/roy/Documents/Programmering/PhysicsEngine/Basic2D/Source
OBJECTDIR = /home/roy/Documents/Programmering/PhysicsEngine/Basic2D/Object

CFLAGS = -I$(INCLUDEDIR) -std=c++11
LDFLAGS = -lGL -lglut
TARGET = PhysicsEngine

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp, $(OBJECTDIR)/%.o, $(SOURCES))

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(CFLAGS) $(LDFLAGS) -o $@

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

clean:
	rm $(OBJECTDIR)/*.o theta.txt d_theta.txt

deepclean:
	rm $(OBJECTDIR)/*.o PhysicsEngine

remake:
	make deepclean; make
