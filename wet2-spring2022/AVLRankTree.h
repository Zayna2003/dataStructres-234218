#ifndef AVLTREES_H_
#define AVLTREES_H_

#include <iostream>
#include "library2.h"
using std::ostream;
using std::string;

template<class T, class S>
class AvlRankTree {
public:
    bool dltData;
    class Node {
    public:
        T key;
        S data;
        int height;
        int bf;
        Node *right;
        Node *left;
        Node *parent;
        int rank;
        ~Node() {}

        Node() = default;

        Node( T &key,  S &data) : key(key), data(data),
                                  height(1), bf(0), right(NULL), left(NULL), parent(NULL), rank(1){}
    };

    class KeyDoesNotExist {
    public:
        string what() const {
            return "KEY_DOES_NOT_EXIST";
        };
    };

    class KeyAlreadyExists {
    public:
        string what() const {
            return "KEY_ALREADY_EXISTS";
        };
    };

//    Node *newNode(T key, S data) {
//        Node *node = new Node();
//        node->key = key;
//        node->data = data;
//        node->left = NULL;
//        node->right = NULL;
//        node->parent = NULL;
//        node->height = 1;
//        node->bf = 0;
//        return node;
//    }
//    int size=0;
    void updateNodeRank(Node *node) {
        int leftRank = getLeftChildRank(node);
        int rightRank = getRightChildRank(node);
        node->rank = 1 + leftRank+rightRank ;

    }



    int LeftSize(Node* node){
        int s=1;
        while(node->left !=NULL){
            s++;
            node=node->left;
        }
        return s;
    }

    int RightSize(Node* node){
        int s=1;
        while(node->right !=NULL){
            s++;
            node=node->right;
        }
        return s;
    }

    StatusType Size(Node *node,int *n){
        if(node !=NULL) {
            Size(node->right,n);
            (*n)++;
            Size(node->left,n);
            //*n = LeftSize(this->root) + RightSize(this->root) - 1;
        }
        return SUCCESS;
    }
    StatusType SizeForL(Node *node,int *n,int *sum){
        if(node !=NULL) {
            SizeForL(node->right,n,sum);
            (*n)+=node->data;
            (*sum)+=(node->key).getGrade();
            SizeForL(node->left,n,sum);
            //*n = LeftSize(this->root) + RightSize(this->root) - 1;
        }
        return SUCCESS;
    }
    int LeftSum(Node* node,int* sum){
        int s=node->data;
        int s2=0;
        s2+=(node->key).getGrade();
        while(node->left !=NULL){
            s+=node->left->data;
            s2+=(node->left->key).getGrade();
            SizeForL(node->left->right,&s,&s2);
            node=node->left;
        }
        (*sum)+=s2;
        return s;
    }

    int RightSum(Node* node){
        int s=node->data;
        while(node->right !=NULL){
            s+=node->right->data;
            node=node->right;
            s+= LeftSum(node)-node->data;
        }

        return s;
    }
    int getLRSum(Node* node,int* sum) {
        if(!(node->left)){
            return LeftSum(node,sum);
        }
        return LeftSum(node,sum); /*+ RightSum(node->left) - node->left->data*/;
    }


    StatusType   GetSumHighestRanks(Node* root ,int m,long long int* level) {
        int x=m;
        long long int l=0;// sum of levels
        int k=0;// num of levels
        GetSumHighestRanksAux(this->root,root, &x, &l,&k);
        (*level)=l;
        return SUCCESS;
    }

    void   GetSumHighestRanksAux(Node* node,Node* root,int* m,long long int *l,int * s){
        if (node && (*m)>=0) {
            GetSumHighestRanksAux(node->right,root,m,l,s);
            if((*m)>0) {
                (*m)--;
                (*l) +=  ((node->key).getGrade());
                (*s)++;
            }
            GetSumHighestRanksAux(node->left,root,m,l,s);
        }
    }

    int getSum(Node* node,int *s){
        if(!node) return 0;
        int s1=0;
        int sum=getLRSum(node,&s1);
        Node* tmp=node->parent;
        while (tmp !=NULL) {
            if ((node->key) > (tmp->key)) {
                sum +=getLRSum(tmp,&s1);
            }
            tmp=tmp->parent;
        }
        *s=s1;
        return sum;
    }

    //  int getRank(Node* node){
    //   updateNodeRank(node);
    //   int rank=node->rank;
    //   Node* temp=node->parent;
    //   while( (temp!=NULL) && (node->key > temp->key)  ){
    //       updateNodeRank(temp);
    //         rank+=temp->rank;
    //         temp=temp->parent;
    // }
    //     return rank;
    //  }


    int getLeftChildRank(Node *node) {
        if (node->left) {
            return node->left->rank;
        }
        return 0;
    }


    int getRightChildRank(Node *node) {
        if (node->right) {
            return node->right->rank;
        }
        return 0;
    }


    int GetBF(Node *node) {
        if (node == NULL)
            return 0;
        return GetNodeHeight(node->left) - GetNodeHeight(node->right);
    }

    S getdata(Node *node) {
        return node->data;
    }

//    Node *getRoot(Node *node) {
//        return node->data;
//    }

    Node *GetLeft(Node *node) {
        if (node == NULL)
            return 0;
        return node->left;
    }

    Node *GetRight(Node *node) {
        if (node == NULL)
            return 0;
        return node->right;
    }

    int GetNodeHeight(Node *node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    void updateHeightANDbf(Node *node) {
        int leftHeight = (node->left == NULL) ? 0 : GetNodeHeight(node->left);
        int rightHeight = (node->right == NULL) ? 0 : GetNodeHeight(node->right);

        int max = (leftHeight - rightHeight) > 0 ? leftHeight : rightHeight;
        node->height = 1 + max;
        //node->bf=rightHeight-leftHeight;
    }
    //~Node() {}

    void RemoveAllNodes(Node *node) {
        if (node) {
            RemoveAllNodes(GetLeft(node));
            RemoveAllNodes(GetRight(node));
            /*if(node->data && dltData){
                delete node->data;
                node->data = nullptr;
            }*/
            //delete node->data;
            //node->data = nullptr;
            delete node;
            node = nullptr;
        }
    }


    Node *root;

    AvlRankTree(bool dltData=false) : root(NULL), dltData(dltData) {}

    ~AvlRankTree() {
        if (root) {
            RemoveAllNodes(this->root);
            this->root= nullptr;
        }
    }

//    void addNode(T key, S data) {
//        this->root = insert(this->root, key, data);
//    }

    Node *insert(Node *node, T key, S data) {
        // TODO: check if key is invalid
        if(this->root == nullptr){
            Node *new_node = new Node(key, data);
            if (!new_node) return NULL;
            this->root = new_node;
            return new_node;
        }
        if(node == NULL){
            return NULL;
        }
        if(node->key == key){
            (node->data)+=data;
            return node;
            //   throw KeyAlreadyExists();
        }

        if(node->key < key || node->key == key){
            if (node->right == nullptr){
                Node *tmp = new Node(key,data);
                tmp->parent = node;
                node->right = tmp;
                updateHeightANDbf(node);
                updateNodeRank(node);
                updateNodeRank(tmp);
                balanceTree(node);
                return tmp;
            }
            insert(node->right, key, data);
        }else{
            if (node->left == nullptr) {
                Node *tmp = new Node(key,data);
                tmp->parent = node;
                node->left = tmp;
                updateHeightANDbf(node);
                updateNodeRank(node);
                updateNodeRank(tmp);
                balanceTree(node);
                return tmp;
            }
            insert(node->left, key, data);
        }

        updateHeightANDbf(node);
        updateNodeRank(node);
        if(node->parent == nullptr){
            this->root = balanceTree(node);
            return this->root;
        }
        else{
            return balanceTree(node);
        }
    }

    Node *balanceTree(Node *node) {
        if(GetBF(node)==2 && GetBF(node->left)==1){
            return LLCase(node);
        }else if(GetBF(node)==-2 && GetBF(node->right)==-1) {
            return RRCase(node);
        }
        else if(GetBF(node)==-2 && GetBF(node->right)==1) {
            return RLCase(node);
        }
        else if(GetBF(node)==2 && GetBF(node->left)==-1) {
            return LRCase(node);
        }

        return node;
    }

    Node *LLCase(Node *node) {
        Node* tmp= RRotation(node);
        updateNodeRank(node);
        updateNodeRank(tmp);
        return tmp;
    }

    Node *LRCase(Node *node) {
        node->left = LRotation(node->left);
        Node* temp= LLCase(node);
        updateNodeRank(temp->right);
        updateNodeRank(temp->left);
        updateNodeRank(temp);
        return temp;
    }

    Node *RRCase(Node *node) {
        Node* tmp= LRotation(node);
        updateNodeRank(node);
        updateNodeRank(tmp);
        return tmp;
    }

    Node *RLCase(Node *node) {
        node->right = RRotation(node->right);
        Node* temp=  RRCase(node);
        updateNodeRank(temp->right);
        updateNodeRank(temp->left);
        updateNodeRank(temp);
        return temp;
    }


    Node *LRotation(Node *node) {
        Node *temp = node->right;
        if(temp!= nullptr){
            node->right = temp->left;
            if(temp->left){
                temp->left->parent = node;
            }
            temp->parent = node->parent;
        }
        if(node->parent && node->parent->right == node){
            node->parent->right=temp;
        }
        if(node->parent && node->parent->left == node){
            node->parent->left=temp;
        }
        if(temp!= nullptr){
            temp->left = node;
        }
        node->parent = temp;
        updateHeightANDbf(node);
        //   updateNodeRank(node);
        updateHeightANDbf(temp);
        //  updateNodeRank(temp);
        return temp;
    }

    Node *RRotation(Node *node) {
        Node *temp = node->left;
        if(temp != nullptr){
            node->left = temp->right;
            if(temp->right){
                temp->right->parent = node;
            }
            temp->parent = node->parent;
        }
        if(node->parent && node->parent->right == node){
            node->parent->right=temp;
        }
        if(node->parent && node->parent->left == node){
            node->parent->left=temp;
        }
        if(temp != nullptr){
            temp->right = node;
        }
        node->parent = temp;
        updateHeightANDbf(node);
        // updateNodeRank(node);
        updateHeightANDbf(temp);
        //updateNodeRank(temp);
        return temp;
    }

    void removeNode(T key) {
        Node* node= findNodeByKey(this->root,key);
        if((node!=NULL) &&((node->data) >1)){
            (node->data)--;
            return;
        }
        this->root = Remove(this->root, key, true);
    }

    void removeNodeForW(T key,S data) {
        Node* node= findNodeByKey(this->root,key);
//        if((node->data) ==data ){
//            (node->data)=1;
//        }
        if((node!=NULL)){
            int old=(node->key).getGrade();
            (node->key).setGrade(old-data);
            (node->data)--;
        }
        if(node && node->data <= 0){
            this->root = Remove(this->root, key, true);
        }
    }

    void removeNodeForMerge(T key) {
        this->root = Remove(this->root, key, true);
    }
    Node *Remove(Node *node, T key, bool dltDataFlag) {
        Node* tmp;
        if (node == NULL) {
            return node;
        }
        S dataToDlt=-1;
        // if node to delete is root or leaf
        if(node->left == nullptr && node->right == nullptr ){
            if(node->key!=key) return NULL;
            if(this->root == node){
                this->root = nullptr;
            }
            if(node->data){
                //delete node->data;
                //node->data = nullptr;
            }

            delete node;
            node = nullptr;
            return NULL;
        }

        // else
        if(node->key < key){
            node->right = Remove(node->right, key, dltDataFlag);
        } else if(node->key > key){
            node->left = Remove(node->left, key, dltDataFlag);
        } else{
            if(node->left != nullptr){
                tmp = max(node->left);
                node->key = tmp->key;
                if(node->data && dltDataFlag){
                    dataToDlt = node->data;
                    dltDataFlag = true;
                }
                node->data = tmp->data;
                tmp->data = dataToDlt;
                node->left = Remove(node->left, tmp->key, dltDataFlag);
            }
            else{
                tmp = min(node->right);
                S dataToDlt = node->data;
                node->key = tmp->key;
                if(node->data && dltDataFlag){
                    dataToDlt = node->data;
                    dltDataFlag = false;
                }
                node->data = tmp->data;
                tmp->data = dataToDlt;
                node->right = Remove(node->right, tmp->key, dltDataFlag);
            }
        }
//        if(dataToDlt){
//            free(dataToDlt) ;
//            dataToDlt = nullptr;
//        }
        updateHeightANDbf(node);
        updateNodeRank(node);
        node = balance_remove(node);
        return node;
    }

    Node *balance_remove(Node *node) {
        if(GetBF(node)==2 && GetBF(node->left)==1){
            return LLCase(node);
        }else if(GetBF(node)==-2 && GetBF(node->right)==-1) {
            return RRCase(node);
        }
        else if(GetBF(node)==-2 && GetBF(node->right)==1) {
            return RLCase(node);
        }
        else if(GetBF(node)==2 && GetBF(node->left)==-1) {
            return LRCase(node);
        }
        else if(GetBF(node)==2 && GetBF(node->left)== 0) {
            return LLCase(node);
        }
        else if(GetBF(node)==-2 && GetBF(node->right)== 0) {
            return RRCase(node);
        }
        return node;
    }


    Node *min(Node *node) {
        Node *temp = node;
        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    bool contains(T key) {
        return treeContains(this->root,  key);
    }
    bool treeContains(Node *node, T key) {
        if (!node) {
            return false;
        }
        int cmp = (key - (node->key));

        if (cmp < 0) return treeContains(node->left, key);

        if (cmp > 0) return treeContains(node->right, key);

        if (cmp == 0) return true;
        else return false;
    }

    S Find(int key) {
        return findNode(root, key);
    }

    S findNode(Node *node, T key) {
        if (!node) {
            return NULL;
        }
        int cmp = (key - (node->key));

        if (cmp < 0) return findNode(node->left, key);
        if (cmp > 0) return findNode(node->right, key);
        if (cmp == 0) {
            return getdata(node);
        } else {
            throw KeyDoesNotExist();
        }
    }
    Node* findNodeByKey(Node *node, T key) {
        if (!node) {
            return NULL;
        }
        int cmp = (key - (node->key));

        if (cmp < 0) return findNodeByKey(node->left, key);
        if (cmp > 0) return findNodeByKey(node->right, key);
        if (cmp == 0) {
            return node;
        } else {
            return NULL;
        }
    }



    void printTree() {
        return print(this->root);
    }

    void print(Node *node ) {
        if (node) {
            std::cout << node->key << " ";
            std::cout << node->data<< " ";
            std::cout << node->rank << "\n ";
            std::cout << getSum(node) << "\n ";
            print(node->left);
            print(node->right);
        }
    }

    void printin(S dataElements, int *numOfPlayers) {
        int j = 0;
        //  dataElements = new S[10];
        //  return
        inorder_(this->root, dataElements, numOfPlayers, &j);

    }

    void printintwo(S* dataElements, int *numOfPlayers) {
        int j = 0;
        //  dataElements = new S[10];
        //  return
        inorder_two(this->root, dataElements, numOfPlayers, &j);

    }

    void inorder_two(Node *node, S* dataElements, int *numOfPlayers, int *j) {

        if (node) {
            inorder_two(node->left, dataElements, numOfPlayers, j);
            dataElements[(*j)++] = (node->data);
            inorder_two(node->right, dataElements, numOfPlayers, j);
        }
        *numOfPlayers = *j;
    }

    void inorder_(Node *node, S dataElements, int *numOfPlayers, int *j) {

        if (node) {
            inorder_(node->left, dataElements, numOfPlayers, j);
            dataElements[(*j)++] = *(node->data);
            inorder_(node->right, dataElements, numOfPlayers, j);
        }
        *numOfPlayers = *j;
    }

    Node *GetMax() {
        return max(root);
    }

    Node *max(Node *node) {
        Node *temp = node;
        while (temp->right != NULL)
            temp = temp->right;

        return temp;
    }

    StatusType GetNumOfPlayersInBounds(T Lower,T Higher,long double *players,long double *sum){
        Node* L=findNodeByKey(this->root,Lower);
        Node* H=findNodeByKey(this->root,Higher);
        if( !L || !H){
            (*players)=0;
            return SUCCESS;
        }
        int sum1=0;
        int sum2=0;
        int RL=getSum(L,&sum1);
        int RH=getSum(H,&sum2);
        if (L==H){
            if((L->data)) {
                (*players)=L->data;
                (*sum)=(L->key).getGrade();
                return SUCCESS;
            }
            (*players)=0;
            return SUCCESS;
        }

        (*players)=RH-RL+(L->data);
        (*sum)=sum2-sum1+((L->key).getGrade());

        return  SUCCESS;
    }

    void GetTreeInOrder(Node** const array) {
        int counter = 0;
        if (this->root != NULL) {
            InOrder(array, this->root, &counter);
        }
        return;
    }

    void  InOrder(Node** const array,Node* const node,int* counter) {
        if (node == NULL) {
            return;
        }
        InOrder(array, node->left, counter);
        array[*counter] = node;
        (*counter)++;
        InOrder(array, node->right, counter);
    }

    void updateData(Node *root, T key,int grade){
        Node* node= findNodeByKey(root,key);
        int old=(node->key).getGrade();
        (node->key).setGrade(grade+old);
    }
};



#endif