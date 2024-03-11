#include "DataVectorSet.h"
#include <fstream>
#include <sstream>
// constructor function which initialises Datavectorset size to given size
// default size is taken as zero
DataVectorSet::DataVectorSet(int size) : set(size) {}
// destructor function which clears all the data in the vector set in datavectorset
DataVectorSet::~DataVectorSet() {
    set.clear();
}
// add function which adds datavector to the set of datavectors
void DataVectorSet::add(const DataVector &t) {
    set.push_back(t);
    return;
}

// filldata function which takes a string and converts it into a datavector and returns it
DataVector DataVectorSet::filldata(const std::string &s) {
    int words = 1;
    std::string tw;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ',')
            words++;
    }
    DataVector temp(words);
    std::istringstream ss(s);
    for (int i = 0; i < words; i++) {
        std::string token;
        if (getline(ss, token, ',')) {
            temp.v[i] = std::stod(token);
        }
    }
    return temp;
}

// readdataset functions takes a file name and reads data in it and adds data to datavectorset after clearing previous data
void DataVectorSet::readdataset(std::string a) {
    std::fstream fin;
    fin.open(a, std::ios::in);
    std::string s;
    set.clear();
    while (std::getline(fin, s)) {
        (*this).add(filldata(s));
    }
    fin.close();
}
