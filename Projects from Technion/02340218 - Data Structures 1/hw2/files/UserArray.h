
#ifndef HW2_RECORDARRAY_H
#define HW2_RECORDARRAY_H
#include "User.h"
#include "AVLTreeExtra.h"
#include "utilesWet2.h"

class UserArray {

public:

    int maxSize;
    int numOfElement;
    AVLTreeExtra<shared_ptr<User>>* table;


    UserArray():maxSize(2), numOfElement(0)
    {
        try {
            table = new AVLTreeExtra<shared_ptr<User>>[maxSize]();
        }
        catch (const std::bad_alloc& e){
            throw std::bad_alloc();
        }


        table[0] = AVLTreeExtra<shared_ptr<User>>(User::compareUsers);
        table[1] = AVLTreeExtra<shared_ptr<User>>(User::compareUsers);

    }

    ~UserArray()
    {
        delete []table;
    }


    void insert(int key, shared_ptr<User> user)
    {
        if(find(key) != nullptr)
        {
            return;
        }

        table[key % maxSize].insertNode(user);
        numOfElement++;
        updateSize();

    }


    void updateSize()
    {
        if(numOfElement == maxSize)
        {
            sizeUP();
        }
    }


    void sizeUP()
    {
        int currentSize = maxSize;
        int counter = 0;
        maxSize = maxSize*2;
        shared_ptr<User>* tempArray = new shared_ptr<User>[numOfElement];
        if(tempArray == nullptr)
            throw std::bad_alloc();
        for(int i = 0; i < currentSize; i++)
        {
            if(table[i].getTreeSize())
            {
                table[i].toArray(tempArray + counter);
                counter += table[i].getTreeSize();
            }
        }
        delete[] table;
        table = nullptr;

        table = new AVLTreeExtra<shared_ptr<User>>[maxSize]();

        for(int i =0;i<maxSize;i++){
            table[i] = AVLTreeExtra<shared_ptr<User>>(User::compareUsers);
        }

        for(int i=0;i < currentSize; i++)
        {
            int key = tempArray[i]->getID();
            table[key % maxSize].insertNode(tempArray[i]);
        }
        delete [] tempArray;
    }


    shared_ptr<User> find(int key)
    {
        shared_ptr<User> tempUser(new User(key,1));
        AVLNode<shared_ptr<User>>* userNode = table[key % maxSize].find(tempUser, nullptr);

        if(userNode == nullptr)
        {
            return nullptr;
        }

        else
        {
            return userNode->getValue();
        }
    }

};


#endif //HW2_RECORDARRAY_H
