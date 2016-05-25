#include "Buffer.h"
#include "Utils.h"
#include "iostream"

int main(int argc, char *argv[]) {
    /*********************************************
          TEST 1 : Method toString for Buffer
    ***********************************************/
    int sizeAckData = SIZE_ACK - SIZE_OPCODE - SIZE_CRC - SIZE_SIZE - 1;
    Buffer ackBuff (SIZE_ACK, 1, OPCODE(ACK_OK), sizeAckData, 0);

    for (int i = 0; i < (SIZE_ACK - SIZE_CRC - DATA_INDEX); i++)
        ackBuff.setData(i, 0xFF);

    std::cout << "Test buff toString Method" << std::endl;
    std::cout << "Expected : " << 1 << OPCODE(ACK_OK) << 0 << sizeAckData
    << 0XFF << 0xFF << 0xFF << 0 << 0 << std::endl;

    std::cout << "Result   : " << ackBuff.toString() << std::endl;




    return EXIT_SUCCESS;
}