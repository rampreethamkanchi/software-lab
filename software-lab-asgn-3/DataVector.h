#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
 * The DataVector class represents a vector of double values.
 * This class provides various operations on vectors such as addition, subtraction, dot product, and distance calculation.
 * It also supports resizing, accessing elements, and retrieving the size(dimension) of the vector.
 */
class DataVector {
  // v is a vector of double values
  vector<double> v;

public:
  DataVector();
  // constructor to initialize the vector with a given string of double values
  DataVector(const vector<string> &row);
  // copy constructor
  DataVector &operator=(const DataVector &other);
  // clear the vector and resize it to the given dimension
  void setDimension(int dimension = 0);
  // plus operator to add two vectors only if they have the same dimension
  DataVector operator+(const DataVector &other);
  // minus operator to add two vectors only if they have the same dimension
  DataVector operator-(const DataVector &other);
  // dot product of two vectors only if they have the same dimension
  double operator*(const DataVector &other);
  // distance between two vectors only if they have the same dimension
  double distance(const DataVector &other) const;
  // returns the dimension of the vector
  int size() const;
  // returns the element at the given index
  double at(int index) const;
  // push the given element to the vector
  void push(double element);
};