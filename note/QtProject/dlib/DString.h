#ifndef DSTRING_H
#define DSTRING_H

#include "DObject.h"
#include "DException.h"

namespace DLib {

using std::ostream;

template<typename T>
class baseString : public DObject<>
{
private:
    T* m_storage;
    size_t m_length;

    void init(const T* str)
    {
        if(length(str))
        {
            m_storage = static_cast<T*>(DObject<>::operator new[](sizeof(T)*length(str)));
            if(m_storage!=NULL)
            {
                strcpy(m_storage, str);
                m_length = length(str);
            }
        }
    }

public:
    baseString(const T* str) : m_storage(NULL), m_length(0) {init(str);}

    baseString() : m_storage(NULL), m_length(0) {init("");}

    baseString(const baseString<T>& str): m_storage(NULL), m_length(0) {init(str.m_storage);}

    baseString(const T& charT) : m_storage(NULL), m_length(0)
    {
        T str[] = {charT, '\0'};
        init(str);
    }

    size_t length(const T* str) const
    {
        size_t len = 0;
        while(*str++ != T() )
               len++;
        return len;
    }

    size_t length() const {return m_length;}

    int strcompare(const T* str1, const T* str2)
    {
        size_t str1len = length(str1);
        size_t str2len = length(str2);
        size_t comparelen = str1len>str2len ? str2len : str1len;
        for(size_t i=0; i<comparelen; i++)
        {
            if(str1[i]!=str2[i])
                return str1[i]<str2[i] ? -1 : 1;
        }
        if(str1len!=str2len)
            return  str1len<str2len ? -1 : 1;
        return 0;
    }

    int strcompare(const baseString<T>& str1, const baseString<T>& str2)
    {
        size_t str1len = str1.length();
        size_t str2len = str2.length();
        size_t comparelen = str1len > str2len ? str2len : str1len;
        for(size_t i=0; i<comparelen; i++)
        {
            if(str1.m_storage[i]!=str2.m_storage[i])
                return str1.m_storage[i]<str2.m_storage[i] ? -1 : 1;
        }
        if(str1len!=str2len)
            return  str1len<str2len ? -1 : 1;
        return 0;
    }

public:
    bool operator ==(const baseString<T>& rval)
    {
        if(strcompare(this->m_storage, rval.m_storage)==0)
            return true;
        else
            return false;
    }

    bool operator ==(const T* str)
    {
        return !strcompare(this->m_storage, str);
    }

    bool operator !=(const T* str)
    {
        return strcompare(this->m_storage, str);
    }

    bool operator !=(const baseString<T>& rval)
    {
        return strcompare(this->m_storage, rval.m_storage);
    }

    ostream operator << (baseString<T>& rval)
    {
        ostream out;
        out.write(rval.m_storage, rval.m_length);
        return out;
    }

    T* toStr() {return m_storage;}

    ~baseString()
    {
        DObject<>::operator delete(m_storage);
    }

};


typedef baseString<char> DString;
typedef baseString<wchar_t> DWString;

}





#endif // DSTRING_H
