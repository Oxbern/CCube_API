#ifndef BUFFER_H
#define BUFFER_H

/*!
 * \file Buffer.h
 * \brief Creates a buffer
 * \version 0.1
 */
#include <cstdint>
#include <iostream>
#include "Debug.h"

/*!
 * \class Buffer
 * \brief Class representing a buffer
 */
class Buffer
{
 private :
    uint8_t header; /*!< Set to 1 if it represents the first buffer of a message, 0 otherwise */
    uint8_t idDevice; /*!< Device's ID */
    int sizeBuffer; /*!< Entire buffer size desired*/
    uint8_t opCode; /*!< Operation code */
    uint16_t sizeLeft; /*!< a message's size left */
    uint8_t *data; /*!< Data contained in the buffer */
    uint16_t crc; /*!< Crc value */
 public :
    /*!
     * \brief Constructor
     *
     * Creates a buffer
     *
     */
    Buffer();

    /*!
     * \brief Constructor
     *
     * Creates a buffer by setting its size
     *
     * \param sizeBuff the buffer's size desired
     */
    Buffer(int sizeBuff);

    /*!
     * \brief Constructor by copy
     *
     */
    Buffer(const Buffer& B);

    /*!
     * \brief Destructor
     *
     */
    ~Buffer();

    /*!
     * \fn void toArray(uint8_t* buffLinear)
     * \brief Converts a buffer into an array
     *
     *
     *
     * \param buffLinear the filled array
     */
    void toArray(uint8_t* buffLinear);

    /*!
     * \fn std::string toString()
     * \brief Prints a buffer
     *
     * Method to string
     *
     */
    std::string toString();

    /*!
     * \fn std::string toStringDebug(int indexInMess)
     * \brief Prints a buffer for debug purposes
     *
     * Method to string
     *
     * \param indexInMess the buffer index in a message
     */
    std::string toStringDebug(int indexInMess);

    /*!
     * \fn void setHeader(uint8_t head)
     * \brief Sets the header of a buffer
     *
     * Setter
     *
     * \param head header (1 or 0)
     */
    void setHeader(uint8_t head);

    /*!
     * \fn void setID(uint8_t id)
     * \brief Sets the device ID of a buffer
     *
     * Setter
     *
     * \param id device's ID
     */
    void setID(uint8_t id);

    /*!
     * \fn void setOpCode(uint8_t code)
     * \brief Sets the operation code of a buffer
     *
     * Setter
     *
     * \param code operation code
     */
    void setOpCode(uint8_t code);

    /*!
     * \fn void setSizeLeft(uint16_t size)
     * \brief Sets the SizeLeft of a buffer
     *
     * Setter
     *
     * \param size the size left in a message
     */
    void setSizeLeft(uint16_t size);

    /*!
     * \fn void setCrc(uint16_t crcCheck)
     * \brief Sets the crc of a buffer
     *
     * Setter
     *
     * \param crcCheck the crc
     */
    void setCrc(uint16_t crcCheck);

    /*!
     * \todo is this method useful ?
     * \fn void setData(int index, uint8_t dataIndex)
     * \brief Sets data[index]
     *
     * Setter
     *
     * \param index the position in data
     * \param dataIndex the value to set
     */
    void setData(int index, uint8_t dataIndex);

    /*!
     * \fn uint8_t getHeader() const
     * \brief Returns the header
     *
     * Getter
     *
     * \return the header of a buffer (1 or 0)
     */
    uint8_t getHeader() const;

    /*!
     * \fn uint8_t getOpCode() const
     * \brief Returns the operation code
     *
     * Getter
     *
     * \return the operation code of a buffer
     */
    uint8_t getOpCode() const;

    /*!
     * \fn uint16_t getSizeLeft() const
     * \brief Returns the left size of a message
     *
     * Getter
     *
     * \return the size left of a buffer
     */
    uint16_t getSizeLeft() const;

    /*!
     * \fn uint8_t *getData() const
     * \brief Returns the data contained in a buffer
     *
     * Getter
     *
     * \return the data contained in a buffer
     */
    uint8_t *getData() const;

    /*!
     * \fn uint16_t getCrc() const
     * \brief Returns the crc
     *
     * Getter
     *
     * \return the crc of a buffer
     */
    uint16_t getCrc() const;

    /*!
     * \fn int getSizeBuffer() const
     * \brief Returns the size of the buffer
     *
     * Getter
     *
     * \return the size of the entire buffer
     */
    int getSizeBuffer() const;

    /*!
     * \fn uint8_t getID() const
     * \brief Returns the ID of the device which this buffer is from or for
     *
     * Getter
     *
     * \return the device ID
     */
    uint8_t getID() const;

    /*!
     * \fn bool operator==(Buffer b)
     * \brief Comparaison operator == between two buffers
     *
     *
     *
     * \return the result of the comparaison
     */
    bool operator==(Buffer b);

    /*!
     * \fn int dataSize(int sizeBuffer);
     * \brief Returns the size available for the data
     *
     *
     * \param sizeBuffer entire size of a buffer
     * \return the size a buffer can contain data
     */
    int getDataSize();

    /*!
     * \fn void crcEncoding()
     * \brief Encodes the crc in the buffer
     */
    void crcEncoding();    
};

/*!
 * \fn int crcIndex(int sizeBuffer)
 * \brief Returns the index of the crc in a buffer
 *
 * 
 * \param sizeBuffer entire size of a buffer
 * \return the index where the crc starts
 */                
int crcIndex(int sizeBuffer);

#endif
