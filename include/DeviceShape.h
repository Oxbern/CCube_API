#ifndef DEVICESHAPE_H
#define DEVICESHAPE_H

/*!
 * \file DeviceShape.h
 * \brief TODO
 * \version 0.1
 */

#include <cstdint>
#include <iostream>

#include "ShapeToDisplay.h"

/*!
 * @class DeviceShape
 * \brief TODO
 */
class DeviceShape
{
 protected :
    int sizeX; /*!< First dimension of the 3D array of booleans (LEDs) */
    int sizeY; /*!< Second dimension of the 3D array of booleans (LEDs) */
    int sizeZ; /*!< Third dimension of the 3D array of booleans (LEDs) */
    bool ***ledStatus; /*!< 3D array of booleans which represent the LEDs of the device */

 public :    
    /*! 
     * \brief Constructor
     * Constructor of the class DeviceShape
     * 
     * \param sizeX  First dimension of the 3D array of booleans
     * \param sizeY  Second dimension of the 3D array of booleans
     * \param sizeZ  Third dimension of the 3D array of booleans
     */
    DeviceShape(int sizeX = 9, int sizeY = 9, int sizeZ = 9);
    
    /*!
     * \brief Destructor
     * Destructor of the class DeviceShape
     */
    ~DeviceShape();

    /*! 
     * \fn bool on(int x, int y, int z)
     * 
     * \brief set the configuration of the LED of coordinates (x, y, z) to true
     *
     * \param x  first coordinate of the LED
     * \param y  second coordinate of the LED
     * \param z  third coordinate of the LED
     * 
     * \return true if the configuration of the LED is now true 
     * false otherwise
     */
    bool on(int x, int y, int z);
    
    /*! 
     * \fn bool off()
     * 
     * \brief Set the configuration of all LEDs to false
     * 
     * \return always return true
     */
    bool off();
    
    /*! 
     * \fn bool off(int x, int y, int z)
     * 
     * \brief set the configuration of the LED of coordinates (x, y, z) to false
     *
     * \param x  first coordinate of the LED
     * \param y  second coordinate of the LED
     * \param z  third coordinate of the LED
     *  
     * \return true if the configuration of the LED is now false 
     * false otherwise
     */
    bool off(int x, int y, int z);
    
    /*! 
     * \fn bool toggle(int x, int y, int z)
     * 
     * \brief set the configuration of the LED of coordinates (x, y, z) to its 
     * opposite (true if it was false and false if it was true)
     * 
     * \param x  first coordinate of the LED
     * \param y  second coordinate of the LED
     * \param z  third coordinate of the LED
     * 
     * \return true if the whole shape stays in the 3D array
     * false otherwise
     */    
    bool toggle(int x, int y, int z);
    
    /*! 
    * \fn int getSizeInBytes()
    * 
    * \brief Returns the nb of uint8_t in the array
    *
    * \return int : nb of uint8_t in the array
    */
    int getSizeInBytes();
    
    /*! 
     * \fn void toArray(uint8_t *arrayToFill)
     * 
     * \brief Write the 3D array in a 1D array
     * 
     * \param arrayToFill  array in which we write
     */
    void toArray(uint8_t *arrayToFill);
    
    /*!
     * \fn friend std::ostream& operator<<(std::ostream& os, const DeviceShape& d)
     * 
     * \brief Overload of the operator <<
     * 
     * \param os  stream on which we write
     * \param d  DeviceShape we display
     * 
     * @return std::ostream& : os (stream we wrote on) 
     */    
    friend std::ostream& operator<<(std::ostream& os, const DeviceShape& d);

    /*! 
     * \fn void print(std::ostream &str) const
     * 
     * \brief Displays the 3D array
     */
    void print(std::ostream &str) const;
    
    /*!
     * \fn DeviceShape& operator=(const DeviceShape &ds)
     * 
     * \brief Overload of the operator =
     * 
     * \param ds  the DeviceShape we want to copy
     * 
     * \return the deviceShape equal to ds 
     */
    DeviceShape& operator=(const DeviceShape &ds);

    /*! 
     * \fn int getSizeX() const
     * 
     * \brief Returns the first dimension of the 3D array
     *
     * \return int sizeX : first dimension of the 3D array
     */
    int getSizeX() const;

    /*! 
    * \fn int getSizeY() const
    * 
    * \brief Returns the second dimension of the 3D array
    *
    * \return int sizeY : second dimension of the 3D array
    */    
    int getSizeY() const;

    /*! 
    * \fn int getSizeZ() const
    * 
    * \brief Returns the third dimension of the 3D array
    *
    * \return int sizeZ : third dimension of the 3D array
    */    
    int getSizeZ() const;
    
    /*! 
    * \fn bool*** getLedStatus() const
    * 
    * \brief Returns the 3D array
    *
    * \return bool ***ledStatus : the 3D array
    */
    bool*** getLedStatus() const;
    
    
    // TODO : test this function
    /*! 
     * \fn bool copyLedStatus(ShapeToDisplay s)
     * 
     * \brief Sets the 3D array to the 3D array
     *  of the ShapeToDisplay
     * 
     * \return true if copy went well
     * false otherwise (for example dimensions did not match)
     */    
    bool copyLedStatus(ShapeToDisplay &s);
};

#endif //DEVICESHAPE_H
