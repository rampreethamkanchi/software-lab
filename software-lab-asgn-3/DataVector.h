#include <iostream>
#include <vector>
 
using namespace std;

class DataVector {
vector<double> v;
public:
DataVector(int dimension=0);
~DataVector();
DataVector(const DataVector& other);
DataVector & operator=(const DataVector &other);
void setDimension(int dimension=0);
DataVector operator+(const DataVector &other);
DataVector operator-(const DataVector &other);
double operator*(const DataVector &other);
};