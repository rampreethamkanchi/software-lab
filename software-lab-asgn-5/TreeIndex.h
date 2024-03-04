#include <iostream>
#include "VectorDataSet.h"
//! check constructor later
class Node {
    public:
    Node *left;
    Node *right;
    VectorDataSet data;
    Node(VectorDataSet &data) : data(data) {
        left = nullptr;
        right = nullptr;
    }
};
class TreeIndex {
protected:
//! initialize minSize
int minSize;
TreeIndex() {}
~TreeIndex() {}
Node * MakeTree(VectorDataSet &S){
    if(S.size() < minSize) {
        return nullptr;
    }
};
public:
static TreeIndex& GetInstance();
};
class KDTreeIndex : public TreeIndex {
public:
static KDTreeIndex& GetInstance();
private:
KDTreeIndex() {}
~KDTreeIndex() {}

};
class RPTreeIndex : public TreeIndex {
public:
static RPTreeIndex& GetInstance();
private:
RPTreeIndex() {}
~RPTreeIndex() {}
};
// procedure MAKETREE(S)

// if |S| < MinSize return (Leaf)

// Rule — CHOOSERULE(S)

// LeftTree — MAKETREE({x € S: Rule(x) = true})

// RightTree — MAKETREE({x € S:: Rule(x) = false})

// return ([Rule, Le ftTree, RightTree})

// The k-d tree CHOOSERULE picks a coordinate direction
// ideally the coordinate with largest spread) and then splits the data on its median value for that coordinate. 

// kd tree  
// choose a coordinate direction i 
// Rule(x) := x < median({z; : z € S}) 
// return (Rule) 
// comment: k-d tree version 

//RP'Tree-Max version
//choose a random unit direction v € R, pick any x € S; let y € S be the farthest point from it,choose delta uniformly at random in [—1, 1] . 6||2 — y||/sqrt(D) where D is the dimension of the vector
//Rule(x) :-= x-v < (median({z-v: z € S}) +6)
//return (Rule)