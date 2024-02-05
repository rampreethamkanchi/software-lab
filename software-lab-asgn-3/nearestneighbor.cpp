// chrono for time calculation
#include <chrono>
// queue for maximum priority queue to store k nearest neighbors
#include <queue>
// fstream for file handling
#include <fstream>
// ssstream for string stream
#include <sstream>
// vector for storing data
#include <iostream>
#include "VectorDataSet.h"

using namespace std;

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
  std::cout << "Time taken for processing data set is : " << duration.count() << " microseconds" << std::endl;
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