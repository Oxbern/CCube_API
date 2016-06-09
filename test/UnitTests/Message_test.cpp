#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <assert.h>

#include "Request.h"
#include "Question.h"
#include "Answer.h"
#include "Utils.h"

#define DEBUG 0

int main(int argc, char *argv[])
{
    /**
     * TEST 1 : Create a "request" message, encode data (with the CRC)
     */

    //Create a request message and encode it
    Request dataMess(2, 92, SET_LEDSTATS);
    uint8_t data[92];
    memset(data, 1, 92);
    dataMess.encode(data);

    //Create the expected first buffer
    std::string dataMessBuffer1Expected;
    dataMessBuffer1Expected = std::to_string(1) + std::to_string(2)
                              + std::to_string(SET_LEDSTATS) + std::string("092");
    for (int i = 0; i < dataMess.getListBuffer()[0].getDataSize(); i++)
        dataMessBuffer1Expected += std::to_string(1);

    dataMessBuffer1Expected += std::to_string(dataMess.getListBuffer()[0].getCrc() >> 8);
    dataMessBuffer1Expected += std::to_string(dataMess.getListBuffer()[0].getCrc() & 0xFF);

#if DEBUG
    std::cout << "\nBuffer 1\n";
    std::cout << dataMess.getListBuffer()[0].toString();

    std::cout << "\nBuffer 1 expected :\n";
    std::cout << dataMessBuffer1Expected << std::endl;
#endif
    assert(dataMessBuffer1Expected == dataMess.getListBuffer()[0].toString());


    //Create the expected second buffer
    std::string dataMessBuffer2Expected;
    dataMessBuffer2Expected = std::to_string(0) + std::to_string(2)
                              + std::to_string(SET_LEDSTATS) + std::string("035");
    for (int i = 0; i < dataMess.getListBuffer()[1].getDataSize(); i++)
        if (i < (92 - dataMess.getListBuffer()[0].getDataSize()))
            dataMessBuffer2Expected += std::to_string(1);
        else
            dataMessBuffer2Expected += std::to_string(0);

    dataMessBuffer2Expected += std::to_string(dataMess.getListBuffer()[1].getCrc() >> 8);
    dataMessBuffer2Expected += std::to_string(dataMess.getListBuffer()[1].getCrc() & 0xFF);

#if DEBUG
    std::cout << "\nBuffer 2\n";
    std::cout << dataMess.getListBuffer()[1].toString();

    std::cout << "\nBuffer 2 expected :\n";
    std::cout << dataMessBuffer2Expected << std::endl;
#endif
    assert(dataMessBuffer2Expected == dataMess.getListBuffer()[1].toString());


    /**
     * TEST 2 : Create a "question" message, encode data (with the CRC)
     */

    Question req(1, GET_LEDSTATS);

    //Create the expected buffer
    std::string questionBufferExpected;
    questionBufferExpected = std::to_string(1) + std::to_string(1)
                              + std::to_string(GET_LEDSTATS) + std::string("00");
    for (int i = 0; i < req.getListBuffer()[0].getDataSize(); i++)
        questionBufferExpected += std::to_string(0);

    questionBufferExpected += std::to_string(req.getListBuffer()[0].getCrc() >> 8);
    questionBufferExpected += std::to_string(req.getListBuffer()[0].getCrc() & 0xFF);

#if DEBUG
    std::cout << "\nBuffer\n";
    std::cout << req.getListBuffer()[0].toString();

    std::cout << "\nBuffer expected :\n";
    std::cout << questionBufferExpected << std::endl;
#endif
    assert(questionBufferExpected == req.getListBuffer()[0].toString());


    /**
    * TEST 3 : Create a "req" message, encode data (with the CRC)
    */

    //Create a message to set the luminosity and encode it
    uint16_t sizeData = 1;
    Request setMess(1, sizeData, SET_LUMINOSITY);

    uint8_t light = 1;
    setMess.encode(&light);

    //Create the expected buffer
    std::string setBufferExpected;
    setBufferExpected = std::to_string(1) + std::to_string(1)
                             + std::to_string(SET_LUMINOSITY) + std::string("01");
    setBufferExpected += std::to_string(light);
    setBufferExpected += std::to_string(setMess.getListBuffer()[0].getCrc() >> 8);
    setBufferExpected += std::to_string(setMess.getListBuffer()[0].getCrc() & 0xFF);

#if DEBUG
    std::cout << "\nSet luminosity message : \n";
    std::cout << setMess.toStringDebug();

    std::cout << "\nSet luminosity message expected : \n";
    std::cout << setBufferExpected << std::endl;
#endif
    assert(setBufferExpected == setMess.getListBuffer()[0].toString());

    
    std::cout << "Test PASSED \n";

    return EXIT_SUCCESS;
}


