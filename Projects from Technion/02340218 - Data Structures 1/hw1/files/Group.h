//
// Created by ofir1 on 02-May-23.
//

#ifndef CS234218_EX1_GROUP_H
#define CS234218_EX1_GROUP_H

#include <memory>
#include "User.h"
#include "AVLTree.h"

using std::shared_ptr;
class Group : public std::enable_shared_from_this<Group>{

private:
    int groupID;
    int groupSize;
    int vipUsers;
    int* genresWatchedCombined;
    int* genresWatchedGroup;
    AVLTree<shared_ptr<User>> usersTree;
public:

//////////Getters&Setters//////////
    int getID() const;
    bool getVIP() const;
    void setGenreGroup(const int genre);
    void setGenreCombined(const int genre, const int both);
    int getSize() const;
    int getGenre(const int genre) const;
    shared_ptr<User> getUser(const int index) const;

    int getGenreGroup(const int genre);
    void removeMeAux(AVLNode<shared_ptr<User>>* user);

//////////Functions//////////
    bool addUser(shared_ptr<User> user);
    bool removeUser(shared_ptr<User> user);
    int getFavoriteGenre() const;
    void groupWatch(const int genre);
    static int compareGroups(const shared_ptr<Group> &a, const shared_ptr<Group> &b);
    void removeMe();

//////////C'trs//////////
    Group(const int GroupID);
    Group(const Group &) = default;
    Group & operator=(const Group &) = default;
    ~Group();
};

#endif //CS234218_EX1_GROUP_H


