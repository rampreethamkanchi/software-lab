#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DataVector {
  vector<double> v;

  public:
  DataVector() {}

  DataVector(const vector<string> &row) {
    for (const string &element : row) {
      v.push_back(stod(element));
    }
  }

  DataVector &operator=(const DataVector &other) {
    if (this != &other) {
      v = other.v;
    }
    return *this;
  }

  void setDimension(int dimension = 0) {
    v.clear();
    v.resize(dimension);
  }

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

  double operator*(const DataVector &other) {
    int lsize = this->size();
    int rsize = other.size();
    double dot_product = 0;
    if (lsize == rsize) {
      DataVector newVector = other;
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
  double distance(const DataVector &other) const{
    int lsize = this->size();
    int rsize = other.size();
    double distance = 0;
    if (lsize == rsize) {
      DataVector newVector = other;
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

  int size() const {
    return v.size();
  }

  double at(int index) const {
    if (index >= v.size()) {
      // handle out-of-range index
    }
    return v[index];
  }

  void push(double element) {
    v.push_back(element);
  }
};

class VectorDataSet {
  vector<DataVector> vs;

  public:
  void push(const DataVector &data_vector) {
    vs.push_back(data_vector);
  }

  int size() const {
    return vs.size();
  }

  const DataVector &at(int index) const {
    if (index >= vs.size()) {
      // handle out-of-range index
    }
    return vs[index];
  }

  void print() const {
    for (const DataVector &data_vector : vs) {
      for (int i = 0; i < data_vector.size(); i++) {
        cout << data_vector.at(i) << " ";
      }
      cout << endl;
    }
  }

  void ReadDataset() {
    cout<<"Reading dataset\n";
    ifstream file("fmnist-train.csv");
    string line, word;

    while (getline(file, line)) {
      stringstream s(line);
      vector<string> row;
      while (getline(s, word, ',')) {
        // cout<<"read a line\n";
        row.push_back(word);
      }
      vs.push_back(DataVector(row));
    }
    cout<<"Dataset read\n";
  }
};

VectorDataSet knearestneighbor(const VectorDataSet &vector_set, const DataVector &data_vector, int k) {
  VectorDataSet near_data_set;
  int size = vector_set.size();
    // priority_queue<double> pq;
    priority_queue<pair<double, int>> pq;
    for(int i = 0; i < size; i++){
      double distance = data_vector.distance(vector_set.at(i));
      if(pq.size() < k)
        pq.push({distance, i});
      else if(pq.top().first > distance){
        pq.pop();
        pq.push({distance, i});
      }
      pq.push({distance, i});
    }
  return near_data_set;
}

int main() {
  VectorDataSet data_set;
  int k;
  data_set.ReadDataset();
//   for (int i = 0; i < data_set.size(); i++) {
//     VectorDataSet near_data_set = knearestneighbor(data_set, data_set.at(i), k);
//     near_data_set.print();
//   }
    VectorDataSet near_data_set = knearestneighbor(data_set, data_set.at(0), k);
    near_data_set.print();

  return 0;
}