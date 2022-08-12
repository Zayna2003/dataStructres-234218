

#include "UnionFind.h"

unionFind::unionFind(int size):size(size){
    size_ = (int*)malloc( sizeof(int)*(size + 1) );
    parents = (int*)malloc( sizeof(int)*(size + 1) );
    data = (double*)malloc( sizeof(double)*(size + 1) );
    sum = (double*)malloc( sizeof(double)*(size + 1) );

    for (int i = 1; i <= size; ++i) {
        parents[i] = -1;
        size_[i] = 1;
        data[i] = 0;
        sum[i] = i;
    }
}

unionFind::~unionFind() {
    free(size_);
    free(parents);
    free(data);
    free(sum);
}

int unionFind::Find(int x, double* returned_data) {
    int parent = this->parents[x];
    int old_p = x;
    double sumData = data[x]+sum[x];
    while (parent > -1){
        old_p = parent;
        sumData+=data[old_p]+sum[old_p];
        parent = this->parents[parent];
    }
    parent = old_p; //parent = root

    if(returned_data!= nullptr){
        *returned_data=sumData;
    }
    int temp = x;
    int new_temp;
    double curr_sum=0;
    sumData=sumData-data[parent]-sum[parent];
    while(parents[temp] != parent && parents[temp] != -1){
        new_temp = parents[temp];
        parents[temp] = parent;

        sumData=sumData-data[temp]-sum[temp];
        curr_sum+=sum[temp];
        data[temp]+=sumData;
        if(new_temp!=parent){
            sum[new_temp]-=curr_sum;
            data[new_temp]+=curr_sum;
        }

        temp = new_temp;
    }
    return parent;
}

void unionFind::Union(int p, int q, double factor) {
    int p_parent = this->parents[p];
    int tmp = p;
    while (p_parent > -1){
        tmp = p_parent;
        p_parent = this->parents[p_parent];
    }
    p_parent = tmp;

    int q_parent = this->parents[q];
    tmp = q;
    while (q_parent > -1){
        tmp = q_parent;
        q_parent = this->parents[q_parent];
    }
    q_parent = tmp;

    p=p_parent;
    q=q_parent;


    // p is the buyer
    if (p == q) return;
 //   if ( size_[p] >= size_[q]) {
        //p is root
        size_[p] += size_[q];
        size_[q]=size_[p];
        parents[q] = p;

        double old_p_sum = sum[p];
        double addition = factor*sum[q] + data[p] + old_p_sum;
        sum[p]=sum[p]+factor*sum[q];
        data[q]=data[q]-addition;
 //   }
//    else{
//        //q is root
//        size_[q] += size_[p];
//        size_[p] = size_[q];
//        parents[p] = q;
//
//        double old_q_sum=sum[q];
//        sum[q]=factor*sum[q]+sum[p]+data[p];
//        data[q]=data[q]-sum[p]-(factor*old_q_sum-old_q_sum)-data[p];
//        data[p]=-data[q]-sum[p];
//    }
}





