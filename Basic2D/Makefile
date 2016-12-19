TARGET = PhysicsEngine

INCLUDEDIR = Include
SOURCEDIR  = Source
OBJECTDIR  = Object

CFLAGS = -I$(INCLUDEDIR) -std=c++11
LDFLAGS = -lGL -lglut

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp, $(OBJECTDIR)/%.o, $(SOURCES))

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(CFLAGS) $(LDFLAGS) -o $@

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $^ -o $@

.PHONY: debug
debug: CFLAGS += -g
debug: $(TARGET)

.PHONY: clean
clean:
	rm $(OBJECTDIR)/*.o

deepclean:
	rm $(OBJECTDIR)/*.o $(TARGET)

remake:
	make deepclean; make
