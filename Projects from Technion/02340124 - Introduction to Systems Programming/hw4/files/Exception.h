#ifndef MTMEX4_EXCEPTION_H
#define MTMEX4_EXCEPTION_H
#include <iostream>

class Exception : public std::exception {};

class DeckFileNotFound : public ::Exception
{
public:
    const char* what() const noexcept override {return "Deck File Error: File not found";}
};

class DeckFileFormatError : public ::Exception
{
private:
    int m_line;
    std::string m_what;
public:
    DeckFileFormatError(int line)
    {
        m_line = line;
        std::string presetMassage = "Deck File Error: File format error in line ";
        std::string lineNumber = std::to_string(m_line);
        std::string tempMassage = presetMassage + lineNumber;
        m_what = tempMassage;
    };
    virtual ~DeckFileFormatError() = default;
    const char* what() const noexcept override
    {
        return m_what.c_str();
    }
};

class DeckFileInvalidSize : public ::Exception
{
public:
    const char* what() const noexcept override { return "Deck File Error: Deck size is invalid";}
};




#endif //MTMEX4_EXCEPTION_H
