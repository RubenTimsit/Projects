//
// Created by ofir1 on 02-May-23.
//
#ifndef CS234218_EX2_AVLTREEEXTRA_H
#define CS234218_EX2_AVLTREEEXTRA_H


#include <memory>

template<class T>
class AVLNode {
    T data;
    AVLNode<T> *left_son;
    AVLNode<T> *right_son;
    AVLNode<T> *parent;
    double height;
    double extra;
    double offset;
public:

    AVLNode() : data(nullptr), left_son(nullptr), right_son(nullptr), parent(nullptr), height(0), extra(0) {}

    explicit AVLNode(const T &value) : data(value), left_son(nullptr), right_son(nullptr), parent(nullptr), height(0), extra(0) {}

    ~AVLNode();

    T getValue() const { return data; }

    void setValue(const T &new_data);

    void setLeft(AVLNode<T> *left) { left_son = left; }

    AVLNode<T> *getLeft() const { return left_son; }

    void setRight(AVLNode<T> *right) { right_son = right; }

    AVLNode<T> *getRight() const { return right_son; }

    void setParent(AVLNode<T> *parent_) { parent = parent_; }

    AVLNode<T> *getParent() const { return parent; }

    int getHeight() const {return this->height;}

    void setUnionHeight(int toAdd) { height = toAdd; }

    void updateHeight();

    int getBalanceFactor() const;

    void toArray(T *array, int *location);

    void resetPrizes();

    void addExtra(double data) {this->extra += data;}

    void setExtra(double data) {this->extra = data;}

    double getExtra() {return this->extra;}

    double getOffset(){ return offset;}

    void setOffset(double toAdd){ offset = toAdd;}


};

template<class T>
class AVLTreeExtra {

    AVLNode<T> *root;

    int (*compare)(const T &a, const T &b);
    // a>b : 1
    // a==b: 0
    // a<b : -1

    void rotateLeft(AVLNode<T> *B);

    void rotateRight(AVLNode<T> *B);

    void insertAux(AVLNode<T> *node, AVLNode<T> *new_node, double* offset = nullptr);

    void rotateByNeed(AVLNode<T> *node);

public:

    explicit AVLTreeExtra(int (*comp)(const T &a, const T &b)) : root(nullptr), compare(comp) {}
    explicit AVLTreeExtra() : root(nullptr){}


    ~AVLTreeExtra();

    AVLNode<T> *removeBinary(const T& data);

    bool insertNode(const T &data, double* offset = nullptr);

    bool removeNode(const T &data);

    bool isEmpty();

    AVLNode<T> *find(const T &value, double* prizes) const;

    AVLNode<T> *findAux(AVLNode<T> *node, const T &value, double* prizes) const;

    AVLNode<T> *getRoot();

    AVLNode<T> *findMinNode(AVLNode<T> *node);

    AVLNode<T> *findMaxNode(AVLNode<T> *node);

    int getTreeSize();

    int getSizeAux(AVLNode<T> *node);

    void toArray(T *array);

    void resetPrizes();


    int calculatePrize(const T &value) const;


    void addPrize(const T &val, double data);

};

template<class T>
void AVLNode<T>::toArray(T *array, int *location) {
    if (this->getLeft() != nullptr)
        this->getLeft()->toArray(array, location);
    array[*location] = this->getValue();
    *location = *location + 1;
    if (this->getRight() != nullptr)
        this->getRight()->toArray(array, location);
}


template<class T>
void AVLNode<T>::resetPrizes(){
    if (this->getLeft() != nullptr)
        this->getLeft()->resetPrizes();
    this->setExtra(0);
    if (this->getRight() != nullptr)
        this->getRight()->resetPrizes();
}


template<class T>
void AVLNode<T>::updateHeight() {
    int left_height = 0;
    int right_height = 0;

    if (right_son == nullptr) {
        right_height = -1;
    } else {
        right_height = right_son->getHeight();
    }

    if (left_son == nullptr) {
        left_height = -1;
    } else {
        left_height = left_son->getHeight();
    }

    this->height = (std::max(left_height, right_height) + 1);
}


template<class T>
int AVLNode<T>::getBalanceFactor() const {
    int left_height, right_height;
    if (left_son == nullptr) {
        left_height = -1;
    } else {
        left_height = left_son->getHeight();
    }
    if (right_son == nullptr) {
        right_height = -1;
    } else {
        right_height = right_son->getHeight();
    }
    return left_height - right_height;
}


template<class T>
AVLNode<T>::~AVLNode() {
    if(left_son != nullptr)
        delete left_son;
    if(right_son != nullptr)
        delete right_son;
}

template<class T>
void AVLNode<T>::setValue(const T &new_data) {
    this->data = new_data;
}


template<class T>
AVLNode<T> *AVLTreeExtra<T>::find(const T &value, double* prizes ) const {
    AVLNode<T> *tmp = this->root;
    return findAux(tmp, value, prizes);
}


template<class T>
AVLNode<T> *AVLTreeExtra<T>::findAux(AVLNode<T> *node, const T &value, double* prizes) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (compare(node->getValue(), value) == 0) {
        if(prizes != nullptr)
            *prizes += node->getExtra();
        return node;
    }
    if (compare(value, node->getValue()) == 1) {
        if(prizes != nullptr)
            *prizes += node->getExtra();
        return findAux(node->getRight(), value, prizes);
    } else {
        if(prizes != nullptr)
            *prizes += node->getExtra();
        return findAux(node->getLeft(), value, prizes);
    }
}



template<class T>
void AVLTreeExtra<T>::addPrize(const T &val, double prize){
    AVLNode<T> *node = this->root;
    bool rowR = false;
    while( node!= nullptr){
        if (compare(node->getValue(), val) == 0) {
            if(node->getRight() != nullptr)
                node->getRight()->addExtra(0);
        }
        if (compare(val, node->getValue()) == 1) {
            if(rowR == false) {
                node->addExtra(prize);
                rowR = true;
            }
            node = node->getRight();
        } else {
            if(rowR == true) {
                node->addExtra(-prize);
                rowR = false;
            }
            node = node->getLeft();
        }
    }
}


template<class T>
void AVLTreeExtra<T>::rotateLeft(AVLNode<T> *B) {
    if (B == nullptr) { return; }

    AVLNode<T> *A = B->getRight();

    AVLNode<T> *A_L = A->getLeft();

    double extraA = A->getExtra();

    A->addExtra(B->getExtra());

    B->addExtra(-A->getExtra());



    if (A_L != nullptr) {
        A_L->addExtra(extraA);
        A_L->setParent(B);
    }

    B->setRight(A_L);

    A->setLeft(B);

    if (B->getParent() == nullptr) {
        this->root = A;
    } else {
        if (B->getParent()->getLeft() == B) {
            B->getParent()->setLeft(A);
        } else {
            B->getParent()->setRight(A);
        }
    }
    A->setParent(B->getParent());
    B->setParent(A);

    B->updateHeight();
    A->updateHeight();


}

template<class T>
void AVLTreeExtra<T>::rotateRight(AVLNode<T> *B) {
    if (B == nullptr) { return; }

    AVLNode<T> *A = B->getLeft();


    double extraA = A->getExtra();

    A->addExtra(B->getExtra());

    B->addExtra(-A->getExtra());


    AVLNode<T> *A_R = A->getRight();
    B->setLeft(A_R);
    if (A_R != nullptr) {
        A_R->addExtra(extraA);
        A_R->setParent(B);
    }




    A->setRight(B);

    if (B->getParent() == nullptr) {
        this->root = A;
    } else {
        if (B->getParent()->getLeft() == B) {
            B->getParent()->setLeft(A);
        } else {
            B->getParent()->setRight(A);
        }
    }
    A->setParent(B->getParent());
    B->setParent(A);

    B->updateHeight();
    A->updateHeight();
}



template<class T>
bool AVLTreeExtra<T>::insertNode(const T &data, double* offset) {



    if (this->find(data, nullptr)) {
        return false;
    }

    auto *new_node = new AVLNode<T>(data);


    if (new_node == nullptr) {
        return false;
    }

    //if our tree is empty
    if (this->root == nullptr) {
        this->root = new_node;
    } else {
        insertAux(this->root, new_node, offset);
    }
    return true;
}


template<class T>
void AVLTreeExtra<T>::insertAux(AVLNode<T> *node, AVLNode<T> *new_node, double* offset) {
    if (compare(node->getValue(), new_node->getValue()) == 1) {

        if (node->getLeft() == nullptr) {
            if(offset != nullptr)
                *offset += node->getExtra();
            node->setLeft(new_node);
            new_node->setParent(node);
        } else {
            if(offset != nullptr)
                *offset += node->getExtra();
            insertAux(node->getLeft(), new_node, offset);
        }
    } else {
        if (node->getRight() == nullptr) {
            if(offset != nullptr)
                *offset += node->getExtra();
            node->setRight(new_node);
            new_node->setParent(node);
        } else {
            if(offset != nullptr)
                *offset += node->getExtra();
            insertAux(node->getRight(), new_node, offset);
        }
    }

    rotateByNeed(node);

}



template<class T>
AVLNode<T> *AVLTreeExtra<T>::findMinNode(AVLNode<T> *node) {
    if (node == nullptr)
        return node;

    if (node->getLeft() == nullptr)
        return node;
    return findMinNode(node->getLeft());
}


template <class T>
AVLNode<T>* AVLTreeExtra<T>::removeBinary(const T& data)
{
    AVLNode<T>* to_delete = find(data, nullptr);

    AVLNode<T>* big_parent = nullptr;


    if (to_delete->getLeft() && to_delete->getRight()) {

        AVLNode<T>* new_root = findMinNode(to_delete->getRight());

        to_delete->setValue(new_root->getValue());
        to_delete = new_root;
        if (to_delete->getRight()) {
            big_parent = to_delete->getRight();
        }
    }

    else if (to_delete->getLeft()) {
        big_parent = to_delete->getLeft();
    } else if (to_delete->getRight()) {
        big_parent = to_delete->getRight();
    }


    AVLNode<T>* parent = to_delete->getParent();
    if (parent == nullptr) {
        root = big_parent;
    } else if (to_delete->getParent()->getLeft() == to_delete) {
        to_delete->getParent()->setLeft(big_parent);
    } else {
        to_delete->getParent()->setRight(big_parent);
    }
    if (big_parent != nullptr) {
        big_parent->setParent(parent);
    }


    to_delete->setLeft(nullptr);
    to_delete->setRight(nullptr);
    delete to_delete;
    return parent;
}



template<class T>
void AVLTreeExtra<T>::rotateByNeed(AVLNode<T> *node) {
    int balance_root = node->getBalanceFactor();

    if (balance_root == 2 && (node->getLeft())->getBalanceFactor() >= 0) {//LL
        rotateRight(node);
        return;
    } else if (balance_root == 2 && (node->getLeft())->getBalanceFactor() == -1) {//LR
        rotateLeft(node->getLeft());
        rotateRight(node);
        return;

    } else if (balance_root == -2 && (node->getRight())->getBalanceFactor() == 1) {//RL
        rotateRight(node->getRight());
        rotateLeft(node);
        return;

    } else if (balance_root == -2 && (node->getRight())->getBalanceFactor() <= 0) {//RR
        rotateLeft(node);
        return;
    }

    node->updateHeight();
}


template<class T>
bool AVLTreeExtra<T>::removeNode(const T &data) {
    if (root == nullptr)
        return false;


    AVLNode<T> *to_delete = this->find(data, nullptr);
    if (to_delete == nullptr)
    {
        return false;
    }


    AVLNode<T> *parent_of_deleted = removeBinary(data);

    while (parent_of_deleted != nullptr) {
        rotateByNeed(parent_of_deleted);
        parent_of_deleted = parent_of_deleted->getParent();
    }
    return true;

}


template<class T>
int AVLTreeExtra<T>::getTreeSize() {
    return getSizeAux(this->root);
}

template<class T>
int AVLTreeExtra<T>::getSizeAux(AVLNode<T> *node) {
    if (node == nullptr)
        return 0;

    return 1 + getSizeAux(node->getLeft()) + getSizeAux(node->getRight());
}

template<class T>
void AVLTreeExtra<T>::toArray(T *array) {
    int location = 0;
    if (root != nullptr)
        root->toArray(array, &location);
}

template<class T>
void AVLTreeExtra<T>::resetPrizes() {
    if (root != nullptr)
        root->resetPrizes();
}



template<class T>
bool AVLTreeExtra<T>::isEmpty() {
    return this->root == nullptr;
}



template<class T>
AVLNode<T> *AVLTreeExtra<T>::getRoot() {
    return this->root;
}


template<class T>
AVLNode<T>* AVLTreeExtra<T>::findMaxNode(AVLNode<T> *node) {
    if(node == nullptr)
        return nullptr;
    if (node->getRight() == nullptr && node->getLeft() == nullptr)
        return node;
    if(node->getRight() != nullptr)
        return findMaxNode(node->getRight());
    return node;
}




template<class T>
AVLTreeExtra<T>::~AVLTreeExtra() {
    delete root;
}



#endif //CS234218_EX2_AVLTREEEXTRA_H
