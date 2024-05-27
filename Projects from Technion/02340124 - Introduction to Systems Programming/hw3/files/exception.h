#ifndef EX3_EXCEPTION_H
#define EX3_EXCEPTION_H

#include "iostream"



class Exception : public std::exception {};
class InvalidArgument : public Exception{};
class EmptyQueue : public Exception{};
class InvalidOperation : public Exception{};





#endif //EX3_EXCEPTION_H
