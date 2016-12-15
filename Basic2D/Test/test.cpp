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

int main(int argc, char** argv) {
    
    int m1 = 1;
    int m2 = 2;

    int m = (m1 > m2) ? m1 : m2;
    
    cout << "m = " << m << endl;
}

