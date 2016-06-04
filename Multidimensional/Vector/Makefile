TARGET = VectorTest

LDFLAGS = -std=c++11

$(TARGET): test.o Vector.o
	$(CXX) $^ $(LDFLAGS) -o $@

test.o: test.cpp Vector.cpp Vector.h
	$(CXX) -c $(LDFLAGS) test.cpp

Matrix.o: Vector.cpp Vector.h
	$(CXX) -c $(LDFLAGS) Vector.cpp

clean:
	rm *.o

clean_deep:
	rm *.o $(TARGET)