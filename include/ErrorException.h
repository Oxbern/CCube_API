#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

/*!
 * \file ErrorException.h
 * \brief Normalises the exceptions for the API
 * \version 0.1
 */

#include <iostream>
#include <sstream> 
#include <exception> 

/*!
 * \class ErrorException
 * \brief Represents the thrown exceptions
 */
class ErrorException : public std::exception
{
 public:
    /*!
     * \brief Constructor
     *
     * Creates an exception
     *
     * \param Msg 
     */
    ErrorException( const std::string Msg );

    /*!
     * \brief Destructor
     */
    virtual ~ErrorException() throw();

    /*!
     * \brief Needed
     */
    virtual const char * what() const throw();

 private:
    std::string msg; /*!< Message printed */
};

#endif //ERROR_EXCEPTION_H
