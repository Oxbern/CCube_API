#include "ErrorException.h"

/*!
 * \brief Constructor
 *
 * TODO
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
 * \brief TODO
 */
const char * ErrorException::what() const throw()
{
    return this->msg.c_str();
}
