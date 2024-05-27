//
// Created by ofir1 on 02-May-23.
//
#ifndef CS234218_EX1_USER_H
#define CS234218_EX1_USER_H
#include <memory>
using std::shared_ptr;
class Group;

class User : public std::enable_shared_from_this<User>{

private:
    const int userID;
    bool isVIP;
    int groupNum;
    int* genresWatched;
    int* previousGroupGenres;
    shared_ptr<Group> currGroup;

public:
//////////C'trs//////////
    User(const int userID, bool isVIP);
    User(const User &) = default;
    User & operator=(const User &) = default;
    ~User();
//
////////////Getters&Setters//////////
    int getID() const;
    bool getVIP() const;
    int getGroupID() const;
    void setGroupID(const int group);
    int* getGenresWatched() const;
    void setGenre(const int genre);
    void setGenreAmount(const int genre,const int amount);
    void setGroupPTR(shared_ptr<Group> group);
    void setGroupsGenre(int* currGroupGenre);
    static int compareUsers(const shared_ptr<User> &a, const shared_ptr<User> &b);
    shared_ptr<Group> getGroupPTR();
    void setPreviousGenre(const int genre, const int num);
    void setZeroPreviousGenre();
//////////Functions//////////
    int getCurrGenre(const int genre) const;





};
#endif //CS234218_EX1_USER_H

