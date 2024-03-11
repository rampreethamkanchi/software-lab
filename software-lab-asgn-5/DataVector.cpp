#include "DataVector.h"
#include <cmath>
#include <stdexcept>

// constructor functions
// initializes the vector size to given dimension
DataVector::DataVector(int dimension) : v(dimension) {}
// initializes the vector to the given vector
DataVector::DataVector(const DataVector &other) : v(other.v) {}

// copy operator which copies a vector to another
DataVector &DataVector::operator=(const DataVector &other) {
    v.clear();
    v = other.v;
    return *this;
}

// set dimension function to clear the vecor and resize it to given dimension
void DataVector::setDimension(int dimension) {
    v.clear();
    v.resize(dimension);
}

//+ operator that adds one vector to another vector
// it checks the dimension of two vectors and throws error if they are not eqaul
DataVector DataVector::operator+(const DataVector &other) const {
    if (v.size() != other.v.size()) {
        throw std::invalid_argument("Vector dimensions are not equal");
    }

    DataVector result;
    result.v.resize(v.size());
    for (int i = 0; i < v.size(); i++) {
        result.v[i] = v[i] + other.v[i];
    }
    return result;
}
//- operator that subtracts one vector from another vector
// it checks the dimension of two vectors and throws error if they are not eqaul
DataVector DataVector::operator-(const DataVector &other) const {
    if (v.size() != other.v.size()) {
        throw std::invalid_argument("Vector dimensions are not equal");
    }

    DataVector result;
    result.v.resize(v.size());
    for (int i = 0; i < v.size(); i++) {
        result.v[i] = v[i] - other.v[i];
    }
    return result;
}

//* operator that finds dot product of two vectors
// it checks the dimension of two vectors and throws error if they are not eqaul
long double DataVector::operator*(const DataVector &other) const {
    if (v.size() != other.v.size()) {
        throw std::invalid_argument("Vector dimensions are not equal");
    }

    long double dp = 0;
    for (int i = 0; i < v.size(); i++) {
        dp += v[i] * other.v[i];
    }
    return dp;
}

// Desuctor function of class Datavector
DataVector::~DataVector() {
    v.clear();
}

// norm function caliculates length of a vector by finding dot product of it self
long double DataVector::norm() {
    long double length = ((*this) * (*this));
    return std::sqrt(length);
}

// dist function which caliculates the distance between two vectors by finding length of difference of two vectors
long double DataVector::dist(const DataVector &a1) {
    DataVector r = (*this) - a1;
    return r.norm();
}