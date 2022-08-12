
#ifndef WET2_unionFind_H
#define WET2_unionFind_H

#include <stdio.h>
#include <stdlib.h>
#include "group.h"
#include "AVLRankTree.h"

class unionFind {
public:
    int size;
    int *parents;
    int *size_;
    Group *array;

    unionFind(int size, Group *array);

    unionFind() : size(0), parents(nullptr), size_(nullptr), array(nullptr) {}

    ~unionFind();

    void makeSet(int x);

    void Union(int p, int q);

    int Find(int x);

};
typedef unionFind *UnionFind;


#endif
