#include <vector>
// implementation of datavector
#ifndef _DataVector_
#define _DataVector_
class DataVector {
public:
    // vector of type double to store cordinates of a vector
    std::vector<double> v;
    // constructor functions
    DataVector(int dimension = 0);
    DataVector(const DataVector &other);
    // copy operator
    DataVector &operator=(const DataVector &other);
    // set dimension operator which clears the vector and initialises to given dimension
    void setDimension(int dimension = 0);
    //+ operator to add two vectors
    DataVector operator+(const DataVector &other) const;
    //- operator to subract a vector from other
    DataVector operator-(const DataVector &other) const;
    //* operator which finds dot product of two vectors
    long double operator*(const DataVector &other) const;
    // norm function to find length of a vector
    long double norm();
    // dist function to calivulate distance between two vectors
    long double dist(const DataVector &a1);
    ~DataVector();
};
#endif
