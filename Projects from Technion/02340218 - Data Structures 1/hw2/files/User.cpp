//
// Created by Ruben on 11/06/2023.
//

#include "User.h"

User::User(int id, int phone): id(id),phone(phone),isMember(false),expenses(0),prizesBeforeIJoined(0)
{

}

int User::getID() const
{
    return id;
}

bool User::getMember() const
{
    return isMember;
}

int User::getExpenses() const
{
    return expenses;
}

int User::getPrizesBeforeIJoined() const
{
    return prizesBeforeIJoined;
}

void User::setMember()
{
    isMember = true;
}

int User::compareUsers(const shared_ptr<User> &a, const shared_ptr<User> &b) {
    int a_id = a->getID();
    int b_id = b->getID();
    if (a_id > b_id)
        return 1;
    else if (a_id == b_id)
        return 0;
    else
        return -1;
}



bool operator==(const User &userA, const User &userB)
{
    if(userA.getID() == userB.getID())
    {
        return true;
    }
    return false;
}

int User::getPhone() const {
    return phone;
}







