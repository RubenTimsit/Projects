//
// Created by ofir1 on 09-Jun-23.
//

#include "UnionFind.h"

UnionFind::UnionFind(int size) : size(size),ctr(0) ,elements(new AVLNode<int>* [size]), sets(new AVLNode<int>* [size]), setsSize(new int[size]){
    for(int i=0;i<size;i++)
        setsSize[i] = 0;
}

void UnionFind::MakeSet(int val){
    auto* tempNode = new AVLNode<int>(ctr );
    if(tempNode == nullptr)
        throw std::bad_alloc();
    sets[ctr] =  tempNode;
    elements[ctr] = tempNode;
    setsSize[ctr] += val;
    ctr++;
}

int UnionFind::Find(int val){
    AVLNode<int>* currNode = elements[val];
    AVLNode<int>* tempCurrNode;
    AVLNode<int>* setRoot = currNode;
    int sumExtra = 0;
    int toSubtract = 0;
    int subTemp = 0;
    while(setRoot->getParent() != nullptr){
        sumExtra += setRoot->getExtra();
        setRoot = setRoot->getParent();
    }
    while(currNode != setRoot){
        subTemp = currNode->getExtra();
        currNode->setExtra(sumExtra - toSubtract);
        toSubtract += subTemp;
        tempCurrNode = currNode;
        currNode = currNode->getParent();
        tempCurrNode->setParent(setRoot);
    }
    return setRoot->getValue();
}

int UnionFind::Union(int b, int a){
    AVLNode<int>* aRoot = elements[Find(a) ];
    AVLNode<int>* bRoot = elements[Find(b) ];


    int aSize = setsSize[aRoot->getValue() ];
    int bSize = setsSize[bRoot->getValue() ];

    if(aSize >= bSize){
        bRoot->setParent(aRoot);
        bRoot->addExtra( setsSize[aRoot->getValue()] - aRoot->getExtra());
        setsSize[aRoot->getValue() ] += bSize;
        setsSize[bRoot->getValue() ] = 0;
    }
    else{
        aRoot->setParent(bRoot);
        bRoot->addExtra(setsSize[aRoot->getValue() ]);
        aRoot->addExtra(-bRoot->getExtra());
        setsSize[bRoot->getValue() ] += aSize;
        setsSize[aRoot->getValue() ] = 0;
    }
    bRoot->setUnionHeight(aSize + bRoot->getHeight() );
    sets[bRoot->getValue() ] = sets[aRoot->getValue()];
    Find(sets[a]->getValue());
    Find(sets[b]->getValue());
    return aRoot->getValue();
}

int UnionFind::getHeight(int id){
    int rootHeight = elements[Find(id) ]->getHeight();
    if(Find(id) == id)
        rootHeight = 0;
    return (elements[id ]->getExtra() + rootHeight);
}

int UnionFind::getCol(int id) {
    return sets[sets[Find(id)]->getValue() ]->getValue();
}

UnionFind::~UnionFind(){
    for(int i =0;i<size;i++){
        if(elements[i] != nullptr)
            delete elements[i];
        if(sets[i] != nullptr)
            sets[i] = nullptr;
    }
    if(elements != nullptr)
        delete [] elements;
    if(sets != nullptr)
        delete [] sets;
    if(setsSize != nullptr)
        delete [] setsSize;
}