#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

#include <iostream>
#include <sstream> 
#include <exception> 

class ErrorException : public std::exception
{
public:
    ErrorException( const char * Msg );
    virtual ~ErrorException() throw();


    virtual const char * what() const throw();
private:
    std::string msg;
};

#endif //ERROR_EXCEPTION_H