#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

/*!
 * \file ErrorException.h
 * \brief TODO
 * \version 0.1
 */

#include <iostream>
#include <sstream> 
#include <exception> 

/*!
 * \class ErrorException
 * \brief TODO
 */
class ErrorException : public std::exception
{
 public:
    /*!
     * \brief Constructor
     *
     * TODO
     *
     * \param Msg 
     */
    ErrorException( const char * Msg );

    /*!
     * \brief Destructor
     */
    virtual ~ErrorException() throw();

    /*!
     * \brief TODO
     */
    virtual const char * what() const throw();

 private:
    std::string msg; /*!< TODO */
};

#endif //ERROR_EXCEPTION_H
