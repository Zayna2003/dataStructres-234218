#ifndef AVLTREES_H_
#define AVLTREES_H_

#include <iostream>

using std::ostream;
using std::string;

template<class T, class S>
class AVLTree {
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

        ~Node() {}

        Node() = default;

        Node(const T &key, const S &data) : key(key), data(data),
                                            height(1), bf(0), right(NULL), left(NULL), parent(NULL){}
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
            delete node->data;
            delete node;
            node = nullptr;
        }
    }


    Node *root;

    AVLTree(bool dltData) : root(NULL), dltData(dltData) {}

    ~AVLTree() {
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
            throw KeyAlreadyExists();
        }

        if(node->key < key || node->key == key){
            if (node->right == nullptr){
                Node *tmp = new Node(key,data);
                tmp->parent = node;
                node->right = tmp;
                updateHeightANDbf(node);
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
                balanceTree(node);
                return tmp;
            }
            insert(node->left, key, data);
        }

        updateHeightANDbf(node);
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
        return RRotation(node);
    }

    Node *LRCase(Node *node) {
        node->left = LRotation(node->left);
        return LLCase(node);
    }

    Node *RRCase(Node *node) {
        return LRotation(node);
    }

    Node *RLCase(Node *node) {
        node->right = RRotation(node->right);
        return RRCase(node);
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
        updateHeightANDbf(temp);
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
        updateHeightANDbf(temp);
        return temp;
    }

    void removeNode(T key) {
        this->root = Remove(this->root, key, true);
    }

    Node *Remove(Node *node, T key, bool dltDataFlag) {
        Node* tmp;
        if (node == NULL) {
            return node;
        }
        S dataToDlt = nullptr;
        // if node to delete is root or leaf
        if(node->left == nullptr && node->right == nullptr){
            if(this->root == node){
                this->root = nullptr;
            }
            if(node->data){
                delete node->data;
                node->data = nullptr;
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

    bool contains(int key) {
        return treeContains(this->root,  key);
    }
    bool treeContains(Node *node, int key) {
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

    S findNode(Node *node, int key) {
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

    void printTree() {
        return print(this->root);
    }

    void print(Node *node) {
        if (node) {
            std::cout << node->key << " ";
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
};



#endif