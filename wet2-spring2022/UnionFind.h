
#ifndef WET2_unionFind_H
#define WET2_unionFind_H

#include <stdio.h>
#include <stdlib.h>
#include "Company.h"
#include "AVLRankTree.h"

class unionFind {
public:
    int size;
    int *parents;
    int *size_;
    double *data;
    double *sum;

    unionFind(int size);

    ~unionFind();

    void Union(int p, int q, double factor);

    int Find(int x, double* returned_data);

};
typedef unionFind *UnionFind;


#endif
