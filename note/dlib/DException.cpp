#include "DException.h"

namespace DLib
{

void DException::init(const char *message, const char *file, int line)
{
    m_message = message ? strdup(message) : NULL;
    if(file!=NULL)
    {
        char sl[16] = {0};
        snprintf(sl, sizeof(sl), "%d", line);
        m_location = static_cast<char*>(malloc( strlen(sl) + strlen(file) + 2));
        if(m_location!=NULL)
        {
            m_location = strcpy(m_location, file);
            m_location = strcat(m_location, ":");
            m_location = strcat(m_location, sl);
        }
    }
    else
        m_location = NULL;

}


DException::DException(const char* message)
{
    init(message, NULL, 0);
}

DException::DException(const char* file, int line)
{
    init(NULL, file, line);
}

DException::DException(const char* message, const char* file, int line)
{
    init(message, file, line);
}


DException::DException(const DException& e)
{
    m_message = strdup(e.m_message);
    m_location = strdup(e.m_location);
}

DException& DException::operator=(const DException& e)
{
    if(this!=&e)
    {
        free(m_message);
        free(m_location);

        m_message = strdup(e.m_message);
        m_location = strdup(e.m_location);
    }
    return *this;
}

const char* DException::message() const
{
    return m_message;
}

const char* DException::location() const
{
    return m_location;
}


DException::~DException()
{
    free(m_location);
    free(m_message);
}

void indexOutOfRange::set_what()
{
    if(m_location!=NULL)
    {
        m_what = static_cast<char*>(malloc(strlen(m_message)+ strlen(m_location) + 2 ));
        m_what = strdup(m_location);
        m_what = strcat(m_what, ":");
        m_what = strcat(m_what, m_message);
    }
}

const char* indexOutOfRange::what()
{
    return m_what;
}

indexOutOfRange::~indexOutOfRange()
{
    free(m_what);
}

indexOutOfRange& indexOutOfRange::operator=(const indexOutOfRange& e)
{
    if(this!=&e){
        DException::operator=(e);
        free(this->m_what);
        this->m_what  = strdup(e.m_what);
    }
    return *this;
}

} /*DLib*/
