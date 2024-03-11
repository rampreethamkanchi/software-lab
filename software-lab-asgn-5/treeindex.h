#include "DataVectorSet.cpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;
class Node {
public:
    vector<DataVector> splitInfo;
    Node *left;
    Node *right;

    Node(vector<DataVector>::iterator begin, vector<DataVector>::iterator end) : splitInfo(begin, end), left(nullptr), right(nullptr) {}
};
class TreeIndex {
protected:
    vector<DataVector> set;
    TreeIndex(vector<DataVector>::iterator begin, vector<DataVector>::iterator end);
    TreeIndex();
    ~TreeIndex();

public:
    static TreeIndex &GetInstance();
    void readdata(vector<DataVector> &arr);
    vector<DataVector> &getdata();
    void adddata(DataVector &data);
    void removedata(int index);
};

class KDTreeIndex : public TreeIndex {
private:
    KDTreeIndex();
    ~KDTreeIndex();

public:
    Node *root = nullptr;
    static KDTreeIndex &GetInstance();
    bool chooserule(const std::vector<DataVector> &S, std::vector<DataVector>::iterator begin, std::vector<DataVector>::iterator end, int &splitDimension, double &median);

    Node *kdtreevec(vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end);
    void clearTree(Node *node);

    void Maketree();
    double calculateDistance(const DataVector &a, const DataVector &b);
    void searchLeafKNearest(Node *leafNode, const DataVector &target, int k, priority_queue<double> &nearestNeighbors);
    vector<double> searchKNearest(DataVector &target, int k);
};
class RPTreeIndex : public TreeIndex {
private:
    RPTreeIndex();
    ~RPTreeIndex();

public:
    Node *root = nullptr;
    static RPTreeIndex &GetInstance();
    void clearTree(Node *node);
    double findFarthestPoint(const DataVector &point, const std::vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end);
    void chooserule(vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end, double &delta);
    Node *rptreevec(vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end);
    void Maketree();
    double calculateDistance(const DataVector &a, const DataVector &b);
    void searchLeafKNearest(Node *leafNode, const DataVector &target, int k, priority_queue<double> &nearestNeighbors);
    vector<double> searchKNearest(DataVector &target, int k);
};