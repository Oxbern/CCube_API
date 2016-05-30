#include "ErrorException.h"

ErrorException::ErrorException( const char * Msg )
{
    std::ostringstream oss;
    oss << "[ERROR] File  " << __FILE__ << " | Function : " << __FUNCTION__ << " : " << Msg << std::endl;
    this->msg = oss.str();
}

ErrorException::~ErrorException() throw() {}

const char * ErrorException::what() const throw()
{
    return this->msg.c_str();
}