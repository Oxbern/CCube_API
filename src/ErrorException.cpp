#include "ErrorException.h"

/**
 * @brief TODO
 */
ErrorException::ErrorException( const char * Msg )
{
    std::ostringstream oss;
    oss << "[ERROR] File  " << __FILE__ << " | Function : " << __FUNCTION__ << " : " << Msg << std::endl;
    this->msg = oss.str();
}

/**
 * @brief TODO
 */
ErrorException::~ErrorException() throw()
{
}

/**
 * @brief TODO
 */
const char * ErrorException::what() const throw()
{
    return this->msg.c_str();
}
