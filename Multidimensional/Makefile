TARGET = MatrixTest

$(TARGET): test.o Matrix.o
	$(CXX) $^ -o $@

test.o: test.cpp Matrix.cpp Matrix.h
	$(CXX) -c test.cpp

Matrix.o: Matrix.cpp Matrix.h
	$(CXX) -c Matrix.cpp

clean:
	rm *.o

clean_deep:
	rm *.o $(TARGET)