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
    
    S s;
    s.a = 2.3;
    s.c = 'x';

    S* sp = &s;

    return 0;
}

