//
// Created by ofir1 on 09-Jun-23.
//

#ifndef CS234218_EX2_UNIONFIND_H
#define CS234218_EX2_UNIONFIND_H
#include "AVLTreeExtra.h"


class UnionFind{

private:
    int size;
    int ctr;
    AVLNode<int>** elements;
    AVLNode<int>** sets;

public:
    int* setsSize;
    explicit UnionFind(int size);

    ~UnionFind();

    int Find(int val);

    void MakeSet(int val);

    int Union(int val1, int val2);

    int getHeight(int id);

    int getCol(int id);

};

#endif //CS234218_EX2_UNIONFIND_H
