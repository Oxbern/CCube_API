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
    listBuffer = std::vector<Buffer*> (0);
}

/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
Message::Message(int sizeBuff, uint16_t size, uint8_t code) :
    sizeBuffer(sizeBuff), sizeData(size), opCode(code), crc(0)
{
    int n = this->NbBuffers();
    listBuffer = std::vector<Buffer*> (n);

    for (int i = 0; i < n; i++)
        listBuffer[i] = new Buffer(sizeBuff);

    listBuffer[0]->setHeader(1);
    
    for (int i = 0; i < n; i++) {
        listBuffer[i]->setOpCode(code);
        listBuffer.at(i)->setSizeLeft(size - i * (SIZE_BUFFER - DATA_INDEX - SIZE_CRC));
    }
}

/**
 * @brief Destructor
 */
Message::~Message()
{
    for (std::vector<Buffer*>::iterator it = listBuffer.begin(); it != listBuffer.end(); ++it) {
        delete *it;
    }
    listBuffer.clear();
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
                listBuffer.at(i)->setData(j, dataToEncode[k]);
            else
                listBuffer.at(i)->setData(j,0);
            j++; k++;
        }
	j = 0;


        uint16_t crcComputed = computeCRC(listBuffer.at(i)->getData(),
                                          sizeof(uint8_t)*(sizeBuffer - DATA_INDEX - SIZE_CRC));
        listBuffer.at(i)->setCrc(crcComputed);
    }
}

Buffer* Message::getBuffer(int index)
{
    return this->listBuffer.at(index); //Can throw out_of_range exception
}

/**
 * @todo else throw exception
 * @brief Finds a buffer based on its opCode and sizeLeft
 * @param opCode 
 * @param sizeLeft
 * @return buffer
 */

Buffer* Message::getBuffer(uint8_t opCode, uint16_t sizeLeft) {
    for (int i = 0; i < NbBuffers(); i++) {
	if (listBuffer.at(i)->getOpCode() == opCode && listBuffer.at(i)->getSizeLeft() == sizeLeft)
	    return listBuffer.at(i);
    }
    return NULL;
}

