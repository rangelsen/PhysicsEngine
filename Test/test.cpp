#include <iostream>
#include <vector>

using namespace std;

int get_neighbor_index(int index, int dir, vector<char> v) {
    int size = v.size(); 
    int output = index + dir;

    if(output >= size)
        output -= size;
    else if(output < 0)
        output += size;

    return output;
}

void combine(vector<char> v) {
    for(unsigned int i = 0; i < v.size(); i++) {

        if(i < v.size() - 1) {

            for(unsigned int j = i + 1; j < v.size(); j++) {
                cout << v.at(i) << " : " << v.at(j) << endl;
            }
        }
    }
}

typedef struct{
    double a;
    char c;
} S;

int main(int argc, char** argv) {
    
	int int_1 = 23;
	int int_2 = 91;

	int* p1 = &int_1;
	int* p2 = &int_2;

	cout << "p1: " << p1 << endl;
	cout << "*p1: " << *p1 << endl;

	cout << "p2: " << p2 << endl;
	cout << "*p2: " << *p2 << endl;

	cout << "EXCHANGE" << endl;
	
	int* temp = p1;
	p1 = p2;
	p2 = temp;

	cout << "OUTPUT" << endl;

	cout << "p1: " << p1 << endl;
	cout << "*p1: " << *p1 << endl;

	cout << "p2: " << p2 << endl;
	cout << "*p2: " << *p2 << endl;

}

