// chrono for time calculation
#include <chrono>
// queue for maximum priority queue to store k nearest neighbors
#include <queue>
// fstream for file handling
#include <fstream>
// ssstream for string stream
#include <sstream>
// vector for storing data
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

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
  DataVector() {}
  // constructor to initialize the vector with a given string of double values
  DataVector(const vector<string> &row) {
    for (const string &element : row) {
      v.push_back(stod(element));
    }
  }
  // copy constructor
  DataVector &operator=(const DataVector &other) {
    if (this != &other) {
      v = other.v;
    }
    return *this;
  }
  // clear the vector and resize it to the given dimension
  void setDimension(int dimension = 0) {
    v.clear();
    v.resize(dimension);
  }
  // plus operator to add two vectors only if they have the same dimension
  DataVector operator+(const DataVector &other) {
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
  // minus operator to add two vectors only if they have the same dimension
  DataVector operator-(const DataVector &other) {
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
  // dot product of two vectors only if they have the same dimension
  double operator*(const DataVector &other) {
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
  // distance between two vectors only if they have the same dimension
  double distance(const DataVector &other) const {
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
  // returns the dimention of the vector
  int size() const {
    return v.size();
  }
  // returns the element at the given index
  double at(int index) const {
    if (index >= v.size()) {
      // handle out-of-range index
    }
    return v[index];
  }
  // push the given element to the vector
  void push(double element) {
    v.push_back(element);
  }
};
// The VectorDataSet class represents a vector of DataVector objects with various operations such as push, size, at, print, and ReadDataset.
class VectorDataSet {
  // vs is a vector of DataVector objects
  vector<DataVector> vs;

  public:
  // push the given DataVector to the vector of DataVector
  void push(const DataVector &data_vector) {
    vs.push_back(data_vector);
  }
  // returns the size of the vector of DataVector
  int size() const {
    return vs.size();
  }
  // returns the DataVector at the given index
  const DataVector &at(int index) const {
    if (index >= vs.size()) {
      // handle out-of-range index
    }
    return vs[index];
  }
  // prints the vector of DataVector
  void print() const {
    // cout << "printing..\n";
    for (const DataVector &data_vector : vs) {
      // cout << "dim of vector is " << data_vector.size() << endl;
      for (int i = 0; i < data_vector.size(); i++) {
        cout << data_vector.at(i) << " ";
      }
      cout << endl;
    }

    // cout << "size of vs is " << vs.size() << endl;

    // for (int i = 0; i < vs.size(); i++) {
    //   for (int j = 0; j < (vs[i]).size(); j++) {
    //     cout << vs[i].at(j) << " ";
    //   }
    // }

    // cout << "printed..\n";
  }
  // reads the dataset from the csv file and stores it in the vector of DataVector
  void ReadDataset() {
    cout << "Reading dataset\n";
    // craeting an ifstream object to read the file
    ifstream file("fmnist-train.csv");
    string line, word;
    // reading the file line by line and storing the values in the vector of DataVector
    while (getline(file, line)) {
      // creating a string stream object to read the line with ',' as separator
      stringstream s(line);
      vector<string> row;
      while (getline(s, word, ',')) {
        // cout<<"read a line\n";
        row.push_back(word);
      }
      // adding the row to the vector of DataVector
      vs.push_back(DataVector(row));
    }
    cout << "Dataset read\n";
  }
};
// returns the k nearest neighbors of the given DataVector from the given VectorDataSet
VectorDataSet knearestneighbor(const VectorDataSet &vector_set, const DataVector &data_vector, int k) {
  VectorDataSet near_data_set;
  int size = vector_set.size();
  // priority queue to store the k nearest neighbors
  priority_queue<pair<double, int>> pq;
  // time starts for calculating the time taken for processing
  std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
  // main logic for finding the k nearest neighbors
  // for each vector in the vector_set, calculate the distance from the given data_vector and store the k nearest neighbors in the priority queue
  for (int i = 0; i < size; i++) {
    double distance = data_vector.distance(vector_set.at(i));
    // if the priority queue is not full, push the distance and index of the vector to the priority queue
    if (pq.size() < k) {
      // cout << "present size : " << pq.size() << endl;
      pq.push({distance, i});
    }
    // if the priority queue is full, check if the distance is less than the top element of the priority queue, if yes, pop the top element and push the new distance and index to the priority queue
     else if (pq.top().first > distance) {
      pq.pop();
      pq.push({distance, i});
    }
  }
  // time stops for calculating the time taken for processing
  std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
  // calculate the time taken for processing in microseconds
  std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time taken for processing your function: " << duration.count() << " microseconds" << std::endl;
  // store the k nearest neighbors in the near_data_set
  while (!pq.empty()) {
    near_data_set.push(vector_set.at(pq.top().second));
    pq.pop();
  }
  return near_data_set;
}

int main() {
  VectorDataSet data_set;
  int k;
  // k=5
  cin >> k;
  data_set.ReadDataset();
  //   for (int i = 0; i < data_set.size(); i++) {
  //     VectorDataSet near_data_set = knearestneighbor(data_set, data_set.at(i), k);
  //     near_data_set.print();
  //   }
  VectorDataSet near_data_set = knearestneighbor(data_set, data_set.at(0), k);
  near_data_set.print();

  return 0;
}