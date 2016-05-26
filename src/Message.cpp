#include "Message.h"
#include "Utils.h"

extern "C" {
#include "crc.h"
}

/**
 * @brief Creates an empty message
 */
Message::Message() : sizeBuffer(0), sizeData(0), opCode(0), crc(0)
{
    std::cout << "Message()1\n";
    listBuffer = new Buffer[0];
    std::cout << "Message()2\n";
}

/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
Message::Message(int sizeBuff, uint16_t size, uint8_t code) :
    sizeBuffer(sizeBuff), sizeData(size), opCode(code), crc(0)
{
    std::cout << "Message(sizebuff, size, code)1\n";
    int n = this->NbBuffers();
    std::cout << "le nombre : " << n << "\n";
    //std::vector<Buffer*> l(n);
    //listBuffer = l;
    //std::cout << "Message(sizebuff, size, code)2\n";
    //listBuffer.resize(n);
    listBuffer = new Buffer[n];
    
    for (int i = 0; i < n; i++){        
        Buffer b(sizeBuff);
        listBuffer[i] = b;
    }
    listBuffer[0].setHeader(1);
    std::cout << "Message(sizebuff, size, code)3\n";
    
    for (int i = 0; i < n; i++) {
        listBuffer[i].setOpCode(code);
        listBuffer[i].setSizeLeft(size - i * (SIZE_BUFFER - DATA_INDEX - SIZE_CRC));
        }
    std::cout << "Message(sizebuff, size, code)4\n";    
}

/**
 * @brief Destructor
 */
Message::~Message()
{
    // std::cout << "~Message()1\n";    
    //     delete [] listBuffer;
    // std::cout << "~Message()2\n";        
}

/**
 * @brief Calculates the number of buffers necessary to create a message
 * @return number of buffers needed
 */
int Message::NbBuffers()
{
    if ((sizeData % (sizeBuffer - DATA_INDEX - SIZE_CRC)) == 0)
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC);
    else
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC) + 1;
}




/**
 * @brief Fills the buffers with the data
 * @param data to encode
 */
void Message::encode(uint8_t *dataToEncode)
{
    int j = 0; int k= 0; int n = NbBuffers();
    for (int i = 0; i < n; i ++) {
        while (j < (sizeBuffer - DATA_INDEX - SIZE_CRC)) {
            if (k < sizeData)
                listBuffer[i].setData(j, dataToEncode[k]);
            else
                listBuffer[i].setData(j,0);
            j++; k++;
        }
        j = 0;


        uint16_t crcComputed = computeCRC(listBuffer[i].getData(),
                                          sizeof(uint8_t)*(sizeBuffer - DATA_INDEX - SIZE_CRC));
        listBuffer[i].setCrc(crcComputed);
    }
}

/**
 * @brief Finds a buffer based on its index
 * @param index
 * @return buffer desired
 */
Buffer* Message::getBuffer(int index)
{
    if (index > NbBuffers() || index < 0)
        throw std::out_of_range("Buffer not found\n");
    if (this->listBuffer  == NULL)
        throw std::out_of_range("Buffer null\n");

    return (this->listBuffer); //Can throw out_of_range exception
}

/**
 * @brief Finds a buffer based on its opCode and sizeLeft
 * @param opCode 
 * @param sizeLeft
 * @return buffer desired
 */

Buffer Message::getBuffer(uint8_t opCode, uint16_t sizeLeft) {
    for (int i = 0; i < NbBuffers(); i++) {
        if (listBuffer[i].getOpCode() == opCode && listBuffer[i].getSizeLeft() == sizeLeft)
            return listBuffer[i];
        else
            throw std::out_of_range("Buffer not found\n");                
    }
    return Buffer();
}

