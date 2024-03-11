#include "DataVector.cpp"
#include <vector>
// Datavectorset class which uses vector of datavectors to store set of vectors
class DataVectorSet {
public:
    std::vector<DataVector> set;
    // constructor of datavectorset class
    DataVectorSet(int size = 0);
    // destructor of detavectorset class
    ~DataVectorSet();
    // add function which adds a detavector to the detavectorset
    void add(const DataVector &b);
    // filldata function which takes a string of doubles and , and convert them into datavector
    DataVector filldata(const std::string &s);
    // readdataset function which reads a csv file and convert them into datavector set
    void readdataset(std::string a);
};