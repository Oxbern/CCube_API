#include "ErrorException.h"

/*!
 * \brief Constructor
 *
 * Creates an exception
 *
 * \param Msg 
 */
ErrorException::ErrorException( const std::string Msg )
{
    std::ostringstream oss;
    oss << "[ERROR] File  " << __FILE__ << " | Function : " << __FUNCTION__ << " : " << Msg << std::endl;
    this->msg = oss.str();
}

/*!
 * \brief Destructor
 */
ErrorException::~ErrorException() throw()
{
}

/*!
 * \brief Needed
 */
const char * ErrorException::what() const throw()
{
    return this->msg.c_str();
}
