#include "Utils.h"

/*!
 * \fn void convert16to8(uint16_t val, uint8_t tab[2])
 * \brief Converts an uint16 into two uint8s
 * \param val to convert
 * \param tab array : the converted values destination
 */ 
void convert16to8(uint16_t val, uint8_t tab[2])
{
    if (tab != NULL) {
        tab[0] = val >> 8;
        tab[1] = 0xFF & val;
    }
}

/*!
 * \fn void packID(uint16_t sizeLeftPack, uint8_t opCodePack, uint8_t tab[3])
 * \brief Creates an array with the pack ID
 * \param sizeLeftPack
 * \param opCodePack
 * \param tab array 
 */
void packID(uint16_t sizeLeftPack, uint8_t opCodePack, uint8_t tab[3])
{
    if (tab != NULL) {
        tab[0] = opCodePack;
        tab[1] = sizeLeftPack >> 8;
        tab[2] = 0xFF & sizeLeftPack;
    }
}

/*!
 * \fn uint16_t convertTwo8to16(uint8_t highValue, uint8_t lowValue)
 * \brief Convert two uint8_t values into an uint16_t
 * \param highValue : the first value
 * \param lowValue : the second value
 * \return the uint16_t gathering the two parameters
 */
uint16_t convertTwo8to16(uint8_t highValue, uint8_t lowValue)
{
    uint16_t res = 0;
    res += (highValue << 8);
    res += lowValue;
    return res;
}

/*!
 * \fn uint16_t computeCRC(uint8_t *data, uint16_t size)
 * \brief Computes the crc on an entire buffer
 * \param data the information in a buffer
 * \param size the entire buffer size minus the crc itself
 * \return crc computed
 */
uint16_t computeCRC(uint8_t *data, uint16_t size)
{
    uint16_t out = 0;
    int bits_read = 0, bit_flag = 0;

    if(data == NULL)
        return 0;

    while(size > 0)
        {
            bit_flag = out >> 15;

            out <<= 1;
            out |= (*data >> bits_read) & 1;

            /* Increment bit counter: */
            bits_read++;
            if(bits_read > 7)
                {
                    bits_read = 0;
                    data++;
                    size--;
                }

            /* Cycle check: */
            if(bit_flag)
                out ^= CRC16;

        }

    int i;
    for (i = 0; i < 16; ++i) {
        bit_flag = out >> 15;
        out <<= 1;
        if(bit_flag)
            out ^= CRC16;
    }

    uint16_t crc = 0;
    i = 0x8000;
    int j = 0x0001;
    for (; i != 0; i >>=1, j <<= 1) {
        if (i & out)
	    crc |= j;
    }

    return crc;
}

/*!
 * \fn void printArray(uint8_t *array, int arraySize)
 * \brief Function to print an array of uint8_t
 * \param array the array to print
 * \param arraySize the array's size
 */
void printArray(uint8_t *array, int arraySize)
{
    if (array != NULL) {
        for (int i = 0; i < arraySize; ++i) {
            std::cout << (int) array[i] << " ";
        }
        std::cout << std::endl;
    }
}

/*!
 * \fn std::string uint8ArrayToString(uint8_t *array, int arraySize)
 * \brief Convert an uint8_t array into a string object
 * \param array the array to print
 * \param arraySize the array's size
 * \return string
 */
std::string uint8ArrayToString(uint8_t *array, int arraySize)
{
    std::string sDebug;
    if (array != NULL && arraySize > 0) {
        for (int k = 0; k < arraySize; ++k)
            sDebug += std::to_string(array[k]);
    }
    return sDebug;
}

/*!
 * \fn bool isAValidAnswerOpcode(int val)
 * \brief Tests if the argument is a valid response
 * \param val operation code to test
 */
bool isAValidAnswerOpcode(int val)
{
    bool retVal = false;
    switch(val) {
        case ACK_OK :
        case ACK_ERR :
        case ACK_NOK :
        case DEVICE_ID :
        case GET_LUMINOSITY :
        case SCREEN_SIZE :
        case FIRMWARE_VERSION :
        case DEVICE_INFO :
        case GET_LEDSTATS :
            retVal = true;
            break;
    }
    return retVal;
}

/*!
 * \fn bool isAnAckOpcode(int val)
 * \brief Tests if the argument is a valid ack opcode
 * \param val operation code to test
 */
bool isAnAckOpcode(int val)
{
    bool retVal = false;
    switch(val) {
        case ACK_OK :
        case ACK_ERR :
        case ACK_NOK :
            retVal = true;
            break;
    }
    return retVal;
}


/*!
 * \fn void printBuffer(std::string name, uint8_t *buffer, uint16_t size)
 * \brief Prints a buffer
 * \param name string
 * \param buffer the buffer to print
 * \param size the buffer's size
 */
void printBuffer(std::string name, uint8_t *buffer, uint16_t size) {

	std::cout << name << ": ";

	for (int i = 0; i < size; ++i)
		std::cout << (int)buffer[i] << " | ";

	std::cout << std::endl;
}
