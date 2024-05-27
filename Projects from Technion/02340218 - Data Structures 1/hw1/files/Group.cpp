//
// Created by ofir1 on 02-May-23.
//

#include "Group.h"
using std::shared_ptr;
//////////Getters&Setters//////////
int Group::getID() const {
    return this->groupID;
}

bool Group::getVIP() const {
    if(this->vipUsers > 0)
        return true;
    return false;
}

int Group::getSize() const{
    return groupSize;
}

int Group::getGenre(const int genre) const{
    return genresWatchedCombined[genre];
}


void Group::setGenreCombined(const int genre,const int both){
    if(both)
        genresWatchedCombined[genre] += groupSize;
    else genresWatchedCombined[genre] += 1;
}

void Group::setGenreGroup(const int genre){
    genresWatchedGroup[genre] ++;
}

int Group::getGenreGroup(const int genre){
    return genresWatchedGroup[genre];
}

void Group::removeMeAux(AVLNode<shared_ptr<User>>* user){
    if(user == nullptr)
        return;
    removeMeAux(user->getLeft());
    for(int i =0;i<5;i++)
        user->getValue()->setGenreAmount(i,genresWatchedGroup[i]);
    user->getValue()->setGroupPTR(nullptr);
    user->getValue()->setZeroPreviousGenre();
    user->getValue()->setGroupID(0);
    removeMeAux(user->getRight());
}

void Group::removeMe(){
    removeMeAux(usersTree.getRoot());
}

bool Group::addUser(shared_ptr<User> user) {
    usersTree.insertNode(user);
    groupSize++;
    if(user->getVIP() == true)
        vipUsers++;
    user->setGroupID(this->getID());
    user->setGroupPTR(shared_from_this());

    int* genres_ptr = user->getGenresWatched();
    for(int i = 0; i < 5; i++){
        genresWatchedCombined[i] += genres_ptr[i];
        user->setPreviousGenre(i,genresWatchedGroup[i]);
    }

    return true;
}


bool Group::removeUser(shared_ptr<User> user) {

    usersTree.removeNode(user);

    if(user->getVIP() == true)
        vipUsers--;

    groupSize--;
    for(int i = 0; i < 5; i++){
        genresWatchedCombined[i] -= user->getCurrGenre(i);
    }
    return true;
}

//returns the favorite genre out of genresWatchedCombined
int Group::getFavoriteGenre() const{
    int highest = 0;
    int index = 0;
    int curr = 0;
    highest = genresWatchedCombined[0];
    for(int i = 1;i<5;i++){
        curr = genresWatchedCombined[i];
        if(curr>highest) {
            highest = curr;
            index = i;
        }
    }
    return index;
}

int Group::compareGroups(const shared_ptr<Group> &a, const shared_ptr<Group> &b){
    int a_id = a->getID();
    int b_id = b->getID();
    if (a_id > b_id)
        return 1;
    else if (a_id == b_id)
        return 0;
    else
        return -1;
}

//////////C'trs//////////
Group::Group(const int groupID):
        groupID(groupID),
        groupSize(0),
        vipUsers(0),
        genresWatchedCombined(new int[5]{0,0,0,0,0}),
        genresWatchedGroup(new int[5]{0,0,0,0,0}),
        usersTree(User::compareUsers){
    if (genresWatchedCombined == nullptr || genresWatchedGroup == nullptr) {
        throw std::bad_alloc();
    }
}

Group::~Group() {
    if (genresWatchedCombined != nullptr)
        delete[] genresWatchedCombined;
    if (genresWatchedGroup != nullptr)
        delete[] genresWatchedGroup;

}
