#include "Utils.h"
#include "Message.h"

extern "C" {
#include "crc.h"
}

/**
 * @brief Creates an empty message
 */
Message::Message() : sizeData(0), opCode(0)
{
    listBuffer = new Buffer[0];
}

/**
 * @brief Creates a message with list of buffers with opcode and sizeLeft
 * @param size of the message
 * @param code operation code
 */
Message::Message(uint16_t size, uint8_t code) : sizeData(size), opCode(code)
{
    int n = this->NbBuffers();
    listBuffer = new Buffer[n];
    
    listBuffer[0].setHeader(1);

    for (int i = 0; i < n; i++) {
        listBuffer[i].setOpCode(code);
        listBuffer[i].setSizeLeft(size - i * DATA_MAX_SIZE);
    }
}


/**
 * @brief Destructor
 */
Message::~Message()
{
    delete [] listBuffer;
}

/**
 * @brief Calculates the number of buffers necessary to create Message
 * @return number of buffers
 */
int Message::NbBuffers()
{
    if ((sizeData % DATA_MAX_SIZE) == 0)
        return sizeData/DATA_MAX_SIZE;
    else
        return sizeData/DATA_MAX_SIZE + 1;
}

/**
 * @brief Fills the buffers with the data
 * @param data to encode
 * @param sizeData data's size
 */
void Message::encode(uint8_t *dataToEncode, uint16_t sizeData)
{
    int j = 0; int k= 0; int n = NbBuffers();
    for (int i = 0; i < n; i ++) {
        while (j < DATA_MAX_SIZE) {
            if (k < sizeData)
                listBuffer[i].setData(j, dataToEncode[k]);
            else
                listBuffer[i].setData(j,0);
            j++; k++;
        }
	j = 0;


        uint16_t crcComputed = computeCRC(listBuffer[i].getData(),
                                          sizeof(uint8_t)*DATA_MAX_SIZE);
        listBuffer[i].setCrc(crcComputed);
    }
}
