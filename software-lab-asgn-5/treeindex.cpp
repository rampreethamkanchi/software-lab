#include "treeindex.h"
using namespace std;
int max_size = 100;

TreeIndex::TreeIndex(vector<DataVector>::iterator begin, vector<DataVector>::iterator end) : set(begin, end) {}
TreeIndex::TreeIndex() {
    DataVectorSet temp;
    temp.readdataset("fmnist-train.csv");
    set.clear();
    for (int i = 0; i < temp.set.size(); i++) {
        set.push_back(temp.set[i]);
    }
}
TreeIndex::~TreeIndex() {}
TreeIndex &TreeIndex::GetInstance() {
    static TreeIndex instance;
    return instance;
}
void TreeIndex::readdata(vector<DataVector> &arr) {
    set.clear();
    for (int i = 0; i < arr.size(); i++) {
        set.push_back(arr[i]);
    }
}
vector<DataVector> &TreeIndex::getdata() {
    return set;
}
void TreeIndex::adddata(DataVector &data) {
    set.push_back(data);
}
void TreeIndex::removedata(int index) {
    set.erase(set.begin() + index);
}

KDTreeIndex::KDTreeIndex() {
    TreeIndex::GetInstance();
}
KDTreeIndex::~KDTreeIndex() {}

KDTreeIndex &KDTreeIndex::GetInstance() {
    static KDTreeIndex instance;
    return instance;
}
bool KDTreeIndex::chooserule(const std::vector<DataVector> &S, std::vector<DataVector>::iterator begin, std::vector<DataVector>::iterator end, int &splitDimension, double &median) {
    int dimension = S[0].v.size();
    double maxSpread = -1.0;

    for (int i = 0; i < dimension; ++i) {
        std::vector<double> values;
        std::for_each(begin, end, [&values, i](const DataVector &vec) { values.push_back(vec.v[i]); });

        std::sort(values.begin(), values.end());
        double spread = values[values.size() - 1] - values[0];

        if (spread > maxSpread) {
            maxSpread = spread;
            splitDimension = i;
            median = values[(values.size() - 1) / 2];
        }
    }
    return true;
}

Node *KDTreeIndex::kdtreevec(vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end) {
    if ((end - begin) <= max_size) {
        return new Node(begin, end);
    }

    int split;
    double median;
    if (!chooserule(dataset, begin, end, split, median)) {
        cout << "Error in finding spread.\n";
    }
    int lcount = 0, rcount = 0;
    std::for_each(begin, end, [&split, &median, &lcount, &rcount](const DataVector &vec) {
        if (vec.v[split] <= median)
        {
            lcount++;
        }
        else
        {
            rcount++;
    } });
    std::sort(begin, end, [split](const DataVector &a, const DataVector &b) { return a.v[split] < b.v[split]; });
    vector<DataVector> temp(1);
    temp[0].setDimension(4);
    temp[0].v[0] = split;
    temp[0].v[1] = median;
    temp[0].v[2] = lcount;
    temp[0].v[3] = rcount;
    Node *currentNode = new Node(temp.begin(), temp.end());

    // Recursively build the left and right subtrees
    currentNode->left = kdtreevec(dataset, begin, begin + lcount);
    currentNode->right = kdtreevec(dataset, begin + lcount, end);

    return currentNode;
}
void KDTreeIndex::clearTree(Node *node) {
    if (node == nullptr)
        return;

    // Recursively delete left and right subtrees
    clearTree(node->left);
    clearTree(node->right);

    // Delete the current node
    delete node;
}

void KDTreeIndex::Maketree() {
    // Clear existing data
    clearTree(root);

    // Build the tree
    root = kdtreevec(set, set.begin(), set.end());
}
double KDTreeIndex::calculateDistance(const DataVector &a, const DataVector &b) {
    double distance = 0.0;
    for (size_t i = 0; i < a.v.size(); ++i) {
        distance += pow(a.v[i] - b.v[i], 2);
    }
    return sqrt(distance);
}

// Recursive function to search for k-nearest neighbors in a leaf node of the KD tree
void KDTreeIndex::searchLeafKNearest(Node *leafNode, const DataVector &target, int k, priority_queue<double> &nearestNeighbors) {
    if (leafNode == nullptr)
        return;

    // Iterate over the points in the leaf node and update nearest neighbors
    for (const DataVector &point : leafNode->splitInfo) {
        double distance = calculateDistance(target, point);

        nearestNeighbors.push(distance);

        // Keep only the top k nearest neighbors
        if (nearestNeighbors.size() > k) {
            nearestNeighbors.pop();
        }
    }
}
vector<double> KDTreeIndex::searchKNearest(DataVector &target, int k) {
    priority_queue<double> nearestNeighbors;

    if (root == nullptr)
        return vector<double>(0);

    Node *current = root;

    // Traverse the tree to find the leaf node containing the target
    while (current->left != nullptr || current->right != nullptr) {
        if (target.v[current->splitInfo[0].v[0]] > current->splitInfo[0].v[1]) {
            if (current->right != nullptr) {
                current = current->right;
            } else {
                break;
            }
        } else {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                break;
            }
        }
    }

    // Perform a refined search in the leaf node
    searchLeafKNearest(current, target, k, nearestNeighbors);

    // Extract the k-nearest neighbors from the priority queue
    vector<double> result;
    while (!nearestNeighbors.empty()) {
        result.push_back(nearestNeighbors.top());
        nearestNeighbors.pop();
    }

    // Reverse the result vector to get the nearest neighbors in the correct order
    reverse(result.begin(), result.end());

    return result;
}

RPTreeIndex::RPTreeIndex() {
    TreeIndex::GetInstance();
}
RPTreeIndex::~RPTreeIndex() {}

RPTreeIndex &RPTreeIndex::GetInstance() {
    static RPTreeIndex temp;
    return temp;
}

void RPTreeIndex::clearTree(Node *node) {
    if (node == nullptr)
        return;

    // Recursively delete left and right subtrees
    clearTree(node->left);
    clearTree(node->right);

    // Delete the current node
    delete node;
}
double RPTreeIndex::findFarthestPoint(const DataVector &point, const std::vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end) {
    double maxDistance = 0.0;
    DataVector farthestPoint;
    for (auto it = begin; it != end; ++it) {
        double distance = (point - *it).norm();
        if (distance > maxDistance) {
            maxDistance = distance;
            farthestPoint = *it;
        }
    }
    return maxDistance;
}
void RPTreeIndex::chooserule(vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end, double &delta) {
    int size = (end - begin);
    DataVector x = *(begin + rand() % size);
    delta = findFarthestPoint(x, dataset, begin, end);
    delta *= 6;
    delta /= sqrt(dataset[0].v.size());
    delta *= (((rand() % 200) / 100.0) - 1);
}
Node *RPTreeIndex::rptreevec(vector<DataVector> &dataset, vector<DataVector>::iterator begin, vector<DataVector>::iterator end) {
    if ((end - begin) <= max_size) {
        return new Node(begin, end);
    }
    DataVector dir(dataset[0].v.size());
    for (int i = 0; i < dir.v.size(); i++) {
        dir.v[i] = rand();
    }
    double len = dir.norm();
    for (int i = 0; i < dir.v.size(); i++) {
        dir.v[i] /= len;
    }
    double delta;
    chooserule(dataset, begin, end, delta);
    auto comparator = [&dir](const DataVector &a, const DataVector &b) {
        return (a * dir) < (b * dir);
    };
    std::sort(begin, end, comparator);
    double median = (*(begin + (end - begin) / 2)) * dir;
    int left = 0;
    for (auto it = begin; it != end; ++it) {
        if ((*it) * dir <= median + delta) {
            left++;
        }
    }
    vector<DataVector> temp(2);
    temp[0] = dir;
    temp[1].setDimension(1);
    temp[1].v[0] = median + delta;
    Node *currentNode = new Node(temp.begin(), temp.end());
    // Recursively build the left and right subtrees
    currentNode->left = rptreevec(dataset, begin, begin + left);
    currentNode->right = rptreevec(dataset, begin + left, end);

    return currentNode;
}
void RPTreeIndex::Maketree() {
    // Clear existing data
    clearTree(root);
    // Build the tree
    root = rptreevec(set, set.begin(), set.end());
}
double RPTreeIndex::calculateDistance(const DataVector &a, const DataVector &b) {
    double distance = 0.0;
    for (size_t i = 0; i < a.v.size(); ++i) {
        distance += pow(a.v[i] - b.v[i], 2);
    }
    return sqrt(distance);
}

// Recursive function to search for k-nearest neighbors in a leaf node of the RP tree
void RPTreeIndex::searchLeafKNearest(Node *leafNode, const DataVector &target, int k, priority_queue<double> &nearestNeighbors) {
    if (leafNode == nullptr) {
        return;
    }
    // Iterate over the points in the leaf node and update nearest neighbors
    for (const DataVector &point : leafNode->splitInfo) {
        double distance = calculateDistance(target, point);

        nearestNeighbors.push(distance);

        // Keep only the top k nearest neighbors
        if (nearestNeighbors.size() > k) {
            nearestNeighbors.pop();
        }
    }
}
vector<double> RPTreeIndex::searchKNearest(DataVector &target, int k) {
    priority_queue<double> nearestNeighbors;

    if (root == nullptr)
        return vector<double>(0);

    Node *current = root;

    // Traverse the tree to find the leaf node containing the target
    while (current->left != nullptr || current->right != nullptr) {
        if ((target * current->splitInfo[0]) > current->splitInfo[1].v[0]) {
            if (current->right != nullptr) {
                current = current->right;
            } else {
                break;
            }
        } else {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                break;
            }
        }
    }

    // Perform a refined search in the leaf node
    searchLeafKNearest(current, target, k, nearestNeighbors);

    // Extract the k-nearest neighbors from the priority queue
    vector<double> result;
    while (!nearestNeighbors.empty()) {
        result.push_back(nearestNeighbors.top());
        nearestNeighbors.pop();
    }

    // Reverse the result vector to get the nearest neighbors in the correct order
    reverse(result.begin(), result.end());

    return result;
}

int main() {
    DataVectorSet test;
    test.readdataset("fmnist-test.csv");
    srand(time(0));
    KDTreeIndex::GetInstance();
    RPTreeIndex::GetInstance();
    auto start_time_make = std::chrono::high_resolution_clock::now();
    KDTreeIndex::GetInstance().Maketree();
    RPTreeIndex::GetInstance().Maketree();
    auto start_time = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 10; j++) {
        vector<double> kd_tree_nearest_neighbors = KDTreeIndex::GetInstance().searchKNearest(test.set[j], 10);
        cout << endl;
        cout << "KP Tree Nearest Distances\n";
        for (int i = 0; i < kd_tree_nearest_neighbors.size(); i++) {
            cout << kd_tree_nearest_neighbors[i] << endl;
        }
        cout << endl;
        cout << "RP Tree Nearest Distances\n";
        vector<double> rp_tree_nearest_neighbors = RPTreeIndex::GetInstance().searchKNearest(test.set[j], 10);
        for (int i = 0; i < rp_tree_nearest_neighbors.size(); i++) {
            cout << rp_tree_nearest_neighbors[i] << endl;
        }
        cout << "________________________________\n";
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    auto duration_make = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_make);
    // std::cout << "Time taken: " << duration.count() / 1000 << " milliseconds" << std::endl;
    // std::cout << "Time taken including maketree: " << duration_make.count() / 1000 << " milliseconds" << std::endl;
    return 0;
}