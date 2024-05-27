#ifndef EX3_HEALTHPOINTS_H
#define EX3_HEALTHPOINTS_H
#include <string>

#include <iostream>


using::std::ostream;
using::std::endl;

class HealthPoints{

private :

    int m_maxHP;
    int m_currentHP;

public:

    class Exception : public std::exception {};
    class InvalidArgument : public Exception{};


    HealthPoints(int maxHP=100);
    ~HealthPoints()=default;
    HealthPoints(const HealthPoints& healthPoints)=default;
    HealthPoints& operator+=(int number);
    HealthPoints& operator-=(int number);
    bool operator !=(const HealthPoints& healthPoints)const;
    bool operator <=(const HealthPoints& healthPoints)const;
    bool operator <(const HealthPoints& healthPoints)const;
    bool operator >=(const HealthPoints& healthPoints)const;
    bool operator >(const HealthPoints& healthPoints)const;
    friend ostream& operator<<(ostream& os, const HealthPoints& healthPoints);
    friend bool operator ==(const HealthPoints& healthPoints1,const HealthPoints& healthPoints2);

};

HealthPoints operator+(int number, const HealthPoints& healthPoints);
HealthPoints operator+(const HealthPoints& healthPoints, int number);
HealthPoints operator-(int number, const HealthPoints& healthPoints);
HealthPoints operator-(const HealthPoints& healthPoints, int number);



#endif //EX3_HEALTHPOINTS_H


//add_executable(mtmEx3 main.cpp TestUtils.h QueueExampleTests.cpp TestMain.cpp Queue.h HealthPointsExampleTest.cpp HealthPoints.cpp HealthPoints.h)