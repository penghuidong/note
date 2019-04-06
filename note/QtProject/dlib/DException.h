#ifndef DEXCEPTION_H
#define DEXCEPTION_H

#include "DObject.h"
#include <cstdio>

namespace DLib
{

#define throw_exception(e, m) (throw e(m, __FILE__, __LINE__))

class DException : public DObject<>
{
protected:
    char* m_message;
    char* m_location;

    void init(const char* message, const char* file, int line);
public:
    DException(const char* message);
    DException(const char* file, int line);
    DException(const char* message, const char* file, int line);

    DException(const DException& e);
    DException& operator=(const DException& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~DException() = 0;
};

class indexOutOfRange : public DException
{
protected:
    char* m_what;
    void set_what();
public:
    indexOutOfRange() : DException(NULL){set_what();}

    indexOutOfRange(const char* message) : DException(message){set_what();}

    indexOutOfRange(const char* file, int line) : DException(file, line){set_what();}
    indexOutOfRange(const char* message, const char* file, int line) :
        DException(message, file, line){set_what();}

    indexOutOfRange(const indexOutOfRange& e) : DException(e){m_what = strdup(e.m_what);}

    indexOutOfRange& operator =(const indexOutOfRange& e);
    const char* what();
    virtual ~indexOutOfRange();
};

class invalidParameter : public DException
{
public:
    invalidParameter() : DException(NULL) {}
    invalidParameter(const char* message) : DException(message){}
    invalidParameter(const char* file, int line) : DException(file, line) {}
    invalidParameter(const char* message, const char* file, int line ) : DException(message,file,line) {}

    invalidParameter(const invalidParameter& e) : DException(e) {}

    invalidParameter& operator =(const invalidParameter& e)
    {
        DException::operator =(e);
        return *this;
    }
};

class arithmeticErr : public DException
{
public:
    arithmeticErr() : DException(NULL) {}
    arithmeticErr(const char* message) : DException(message){}
    arithmeticErr(const char* file, int line) : DException(file, line) {}
    arithmeticErr(const char* message, const char* file, int line ) : DException(message,file,line) {}

    arithmeticErr(const arithmeticErr& e) : DException(e) {}

    arithmeticErr& operator =(const arithmeticErr& e)
    {
        DException::operator =(e);
        return *this;
    }
};

class invalidOperation : public DException
{
public:
    invalidOperation() : DException(NULL) {}
    invalidOperation(const char* message) : DException(message){}
    invalidOperation(const char* file, int line) : DException(file, line) {}
    invalidOperation(const char* message, const char* file, int line ) : DException(message,file,line) {}

    invalidOperation(const invalidOperation& e) : DException(e) {}

    invalidOperation& operator =(const invalidOperation& e)
    {
        DException::operator =(e);
        return *this;
    }
};


class outOfMemory : public DException
{
public:
    outOfMemory() : DException(NULL) {}
    outOfMemory(const char* message) : DException(message){}
    outOfMemory(const char* file, int line) : DException(file, line) {}
    outOfMemory(const char* message, const char* file, int line ) : DException(message,file,line) {}

    outOfMemory(const outOfMemory& e) : DException(e) {}

    outOfMemory& operator =(const outOfMemory& e)
    {
        DException::operator =(e);
        return *this;
    }
};


}/* DLib */
#endif // DEXCEPTION_H
