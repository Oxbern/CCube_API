#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

#include <iostream>
#include <sstream> 
#include <exception> 

class ErrorException : public std::exception
{
public:
    ErrorException( const char * Msg )
    {
        std::ostringstream oss;
        oss << "[ERROR] File  " << __FILE__ << " | Function : " << __FUNCTION__ << " : " << Msg << std::endl;
        this->msg = oss.str();
    }

    virtual ~ErrorException() throw()
    {

    }

    virtual const char * what() const throw()
    {
        return this->msg.c_str();
    }

private:
    std::string msg;
};

#endif //ERROR_EXCEPTION_H