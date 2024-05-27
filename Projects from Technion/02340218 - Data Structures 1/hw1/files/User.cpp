//
// Created by ofir1 on 02-May-23.
//
#include "User.h"
#include "Group.h"
#include "wet1util.h"
using std::shared_ptr;
int User::getID() const {
    return this->userID;
}

int User::getGroupID() const {
    return this->groupNum;
}

bool User::getVIP() const {
    return this->isVIP;
}

int* User::getGenresWatched() const {
    return this->genresWatched;
}
void User::setGenreAmount(const int genre,const int amount){
    genresWatched[genre] += amount - previousGroupGenres[genre];
}

//user_genre + curr_group_genre - prev_group_genre
int User::getCurrGenre(const int genre) const{
    if(currGroup!=nullptr) {
        int norm = 0;
        if(currGroup->getGenreGroup(genre) > 0){
            norm = currGroup->getGenreGroup(genre);
        }
        return (genresWatched[genre] + norm - previousGroupGenres[genre]);
    }
    else
        return genresWatched[genre];
}

void User::setGroupID(const int group){
    this->groupNum = group;
}

void User::setGenre(const int genre) {
    if (currGroup != nullptr)
        currGroup->setGenreCombined(genre,0);
    this->genresWatched[genre]++;
}

void User::setPreviousGenre(const int genre, const int num){
    if(currGroup != nullptr)
        previousGroupGenres[genre] += num;
}

void User::setGroupsGenre(int* currGroupGenre){
    for(int i = 0;i<5;i++){
        previousGroupGenres[i] += currGroupGenre[i];
    }
}


void User::setGroupPTR(shared_ptr<Group> group){
    currGroup = group;
}

shared_ptr<Group> User::getGroupPTR(){
    return currGroup;
}
void User::setZeroPreviousGenre(){
    for(int i =0;i<5;i++)
        previousGroupGenres[i] = 0;
}

int User::compareUsers(const shared_ptr<User> &a, const shared_ptr<User> &b){
    int a_id = a->getID();
    int b_id = b->getID();
    if (a_id > b_id)
        return 1;
    else if (a_id == b_id)
        return 0;
    else
        return -1;
}

User::User(const int userID, bool isVIP):
    userID(userID),
    isVIP(isVIP),
    groupNum(0),
    genresWatched(new int[5]{0,0,0,0,0}),
    previousGroupGenres(new int[5]{0,0,0,0,0}),
    currGroup(nullptr){
    if (genresWatched == nullptr || previousGroupGenres == nullptr) {
        throw std::bad_alloc();
    }
}

User::~User() {
    if (this->genresWatched != nullptr) {
        delete[] this->genresWatched;
    }
    if (this->previousGroupGenres != nullptr) {
        delete[] this->previousGroupGenres;
    }
}


