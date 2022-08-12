

#include "UnionFind.h"

unionFind::unionFind(int size, Group *array):size(size),array(array){
     size_ =  (int*)malloc( sizeof(int)*(size + 1) );
            //new int [size];
     parents =(int*)malloc( sizeof(int)*(size + 1) );
            //new int [size];

    for (int i = 0; i < size; ++i) {
        parents[i] = -1;
        size_[i] = 0;
    }
}

unionFind::~unionFind() {
    //this->array =NULL;
    //delete [] size_;
   // delete [] parents;
   free(size_);
   free(parents);
}

void unionFind::makeSet(int x) {
    this->parents[x] = -1;
    this->size_[x] = 1;
}

int unionFind::Find(int x) {
    int parent = this->parents[x];
    int old_p = x;
    while (parent > -1){
        old_p = parent;
        parent = this->parents[parent];
    }
    parent = old_p;
    int temp = x;
    int new_temp;
    while(temp != parent){
        new_temp = parents[temp];
        parents[temp] = parent;
        temp = new_temp;
    }
    return parent;
}

void unionFind::Union(int p, int q) {
    if (p == q) return;
    if ( size_[p] > size_[q]) {
        size_[p] += size_[q]-1;
        size_[q]=0;
        parents[q] = p;
        MergeGroups(*array[p], *array[q]);


    }
    else if (size_[p] < size_[q]) {
        size_[q] += size_[p]-1;
        size_[p] = 0;
        parents[p] = q;
        MergeGroups(*array[q], *array[p]);

    }
    else {
        if (p > q) {
            size_[p] += size_[q]-1;
            size_[q]=0;
            parents[q] = p;
            MergeGroups(*array[p], *array[q]);

        }
        else {
            size_[q] += size_[p]-1;
            size_[p] = 0;
            parents[p] = q;
            MergeGroups(*array[q],*array[p]);

        }
    }
}





