#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


vector<int> generateVector( ) {
    int capacity = rand( ) % 10;

    vector<int> v;
    v.reserve(capacity);
    for (int i = 0; i < capacity; ++i) {
        v.push_back(rand( ) % 100);
    }

    cout << "tempVector:" << &v << endl;
    cout << "tempVector[0]:" << &v[0] << endl;

    return std::move(v);
}

void showVectorInfo(const vector<int> &nums) {
    cout << "vector's size = " << nums.size( ) << endl;
    cout << "vector's capacity = " << nums.capacity( ) << endl;
    cout << "vector's elements: " << endl;


    for (const auto &num : nums) {
        cout << num << " ";
    }
    cout << endl;
    cout << endl;
}


void showV2VectorInfo(const vector<vector<int>> &nums) {
    cout << "v2vector's size = " << nums.size( ) << endl;
    cout << "v2vector's capacity = " << nums.capacity( ) << endl;
    cout << "v2vector's elements: " << endl;
    cout << "########" << endl;


    // for (const auto &v : nums) {
    for (const auto &v : nums) {
        showVectorInfo(v);
    }
    cout << endl;
}


int main(void) {

    srand(time(NULL));

    vector<vector<int>> *v2v = new vector<vector<int>>;

    for (int i = 0; i < 2; ++i) {
        v2v->push_back(std::move(generateVector( )));
    }

    showV2VectorInfo(*v2v);


    cout << "v2Vector:" << &v2v << endl;
    cout << "v2Vector[0]:" << &v2v[0] << endl;
    cout << "v2Vector[0][0]:" << &v2v[0][0] << endl;


    delete v2v;
    return 0;
}
