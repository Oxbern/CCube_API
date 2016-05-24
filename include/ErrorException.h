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
        oss << "File  " << __FILE__ << " | Function : " << __FUNCTION__ << " : " << Msg;
        this->msg = oss.str();
    }

    virtual ~my_exception() throw()
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