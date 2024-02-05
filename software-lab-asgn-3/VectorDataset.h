#include "DataVector.cpp"

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