#include "DataVector.h"
#include <iostream>

using namespace std;

DataVector::DataVector() {}

DataVector::DataVector(const vector<string> &row) {
  for (const string &element : row) {
    v.push_back(stod(element));
  }
}

DataVector &DataVector::operator=(const DataVector &other) {
  if (this != &other) {
    v = other.v;
  }
  return *this;
}

void DataVector::setDimension(int dimension) {
  v.clear();
  v.resize(dimension);
}

DataVector DataVector::operator+(const DataVector &other) {
  int lsize = this->size();
  int rsize = other.size();
  if (lsize == rsize) {
    DataVector newVector = other;
    int size = v.size();
    for (int i = 0; i < size; i++) {
      newVector.v[i] += v[i];
    }
    return newVector;
  } else {
    cout << "only same dimension vectors can be used\n";
    exit(1);
  }
}

DataVector DataVector::operator-(const DataVector &other) {
  int lsize = this->size();
  int rsize = other.size();
  if (lsize == rsize) {
    DataVector newVector = *this;
    int size = other.size();
    for (int i = 0; i < size; i++) {
      newVector.v[i] -= other.v[i];
    }
    return newVector;
  } else {
    cout << "only same dimension vectors can be used\n";
    exit(1);
  }
}

double DataVector::operator*(const DataVector &other) {
  int lsize = this->size();
  int rsize = other.size();
  double dot_product = 0;
  if (lsize == rsize) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
      dot_product += v[i] * other.v[i];
    }
    return dot_product;
  } else {
    cout << "only same dimension vectors can be used\n";
    exit(1);
  }
}

double DataVector::distance(const DataVector &other) const {
  int lsize = this->size();
  int rsize = other.size();
  double distance = 0;
  if (lsize == rsize) {
    int size = v.size();
    for (int i = 0; i < size; i++) {
      distance += (v[i] - other.v[i]) * (v[i] - other.v[i]);
    }
    return distance;
  } else {
    cout << "only same dimension vectors can be used\n";
    exit(1);
  }
}

int DataVector::size() const {
  return v.size();
}

double DataVector::at(int index) const {
  if (index >= v.size()) {
    // handle out-of-range index
  }
  return v[index];
}

void DataVector::push(double element) {
  v.push_back(element);
}
