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

int main(int argc, char** argv) {
    
    vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    v.push_back('d');
    v.push_back('e');
    v.push_back('f');
    v.push_back('g');
    v.push_back('h');
    v.push_back('i');
    v.push_back('j');

    combine(v);
}

