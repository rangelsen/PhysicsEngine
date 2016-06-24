TARGET = MatrixTest

LDFLAGS = -std=c++11

$(TARGET): test.o Matrix.o Vector.o
	$(CXX) $^ $(LDFLAGS) -o $@

test.o: test.cpp Matrix.cpp Matrix.h
	$(CXX) -c $(LDFLAGS) test.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(CXX) -c $(LDFLAGS) Matrix.cpp

Vector.o: Vector.cpp Vector.h
	$(CXX) -c $(LDFLAGS) Vector.cpp

clean:
	rm *.o

clean_deep:
	rm *.o $(TARGET)