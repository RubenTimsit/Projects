#ifndef HW2_USER_H
#define HW2_USER_H
#include <memory>
#include <cstdlib>

using std::shared_ptr;


class User{

private:
    int id;
    int phone;
    bool isMember;
    double expenses;
    int prizesBeforeIJoined;


public:

    User(int id, int phone);
    User()=default;
    ~User()=default;
    User(const User &) = default;

    int getID() const;
    int getPhone() const;
    bool getMember() const;
    int getExpenses() const;
    int getPrizesBeforeIJoined() const;
    void setMember();
    void addExpenses(double val) { expenses += val;}
    void resetExpenses() {expenses = 0;}
    void setOffset(double toSet) { prizesBeforeIJoined = toSet;}
    void resetPrizesOffset() {prizesBeforeIJoined = 0;}

    friend bool operator==(const User& userA, const User& userB);

    static int compareUsers(const shared_ptr<User> &a, const shared_ptr<User> &b);




};


#endif //HW2_USER_H
