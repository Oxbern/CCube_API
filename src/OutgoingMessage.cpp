#include <sstream>

#include "ErrorException.h"
#include "OutgoingMessage.h"
#include "Utils.h"
#include "Debug.h"

/*!
 * \brief Constructor
 *
 * Creates a message
 *
 * \param id device's ID
 * \param sizeBuff the buffers' size
 * \param size the size of the data to encode
 * \param code the message's operation code
 */
OutgoingMessage::OutgoingMessage(uint8_t id, int sizeBuff, uint16_t size, uint8_t code) :
    idDevice(id), sizeBuffer(sizeBuff), sizeData(size), opCode(code)
{
    int nbBuff = this->NbBuffers();

    listBuffer = reinterpret_cast<Buffer *>(new char[nbBuff * sizeof(Buffer)]);

    for (int i = 0; i < nbBuff; i++)
        new(&listBuffer[i]) Buffer(sizeBuff);

    //First buffer first bit should be 1 and others 0
    listBuffer[0].setHeader(1);


    for (int i = 0; i < nbBuff; i++) {
        listBuffer[i].setID(id);
        listBuffer[i].setOpCode(code);
        listBuffer[i].setSizeLeft(size - i * (SIZE_BUFFER - DATA_INDEX - SIZE_CRC));
    }
    LOG(1, "OutgoingMessage(id, sizeBuff, size, code)");
    LOG(2, "OutgoingMessage(ID = " + std::to_string(id)
        + ", OPCODE = " + std::to_string(code)
        + ", SIZEBUFF = " + std::to_string(sizeBuff)
        + ", SIZEDATA = " + std::to_string(size)  + ")");
}

/*!
 * \brief Constructor by copie
 *
 * Creates a message by copying another one
 *
 * \param M the other message which will be unchanged
 */
OutgoingMessage::OutgoingMessage(const OutgoingMessage& M)
{
    sizeBuffer= M.getSizeBuffer();
    sizeData = M.getSizeData();
    opCode = M.getOpCode();
    idDevice = M.getID();
    int n = M.NbBuffers();

    listBuffer = reinterpret_cast<Buffer *>(new char[n*sizeof(Buffer)]);

    for (int i = 0; i<n; i++)
        listBuffer[i] = M.getListBuffer()[i];
    LOG(1, "OutgoingMessage(const &message)");
}

/*!
 * \brief Destructor
 */
OutgoingMessage::~OutgoingMessage()
{
    int n = this->NbBuffers();

    for (int i = 0; i < n; i++)
        listBuffer[i].Buffer::~Buffer();

    delete[] reinterpret_cast<char *>(listBuffer);
    LOG(1, "~OutgoingMessage()");
}

/*!
 * \brief Sends a message to a device
 * \param c controller
 * \return true if the message was sent properly
 */
bool OutgoingMessage::send(Controller &c)
{
    std::cout << "Outgoing message send \n";
    if (c.getConnectedDevice() == NULL)
        return false;

    LOG(2, "[SEND] Send a message :\n" + this->toStringDebug());

    int n = this->NbBuffers();

    for (int i = 0; i < n; i++) {
        LOG(5, "[SEND] Buffer N° " + std::to_string(i));

        // Convert the buffer i into an array
        uint8_t *bufferArray = new uint8_t[sizeBuffer];
        listBuffer[i].toArray(bufferArray);

        int nbTry = 0;

        do {
            // Send the message to the device
            if (!(c.getConnectedDevice()->writeToFileDescriptor(bufferArray,
                                                                sizeBuffer))) {
                throw ErrorException("Error while sending a message : "
                                     "Number of tries to send "
                                     "the message exceeded");
                c.disconnectDevice();
            } /* Buffer sent */
            LOG(5, "Buffer sent");
            
            // ack, response ?
            if (!c.secure)
                break;
            
        } while (++nbTry < MAX_TRY);

        //If number of tries exceeded
        if (nbTry == MAX_TRY) {
            LOG(2, "[HANDLER] NB TRY EXCEDEED");

            throw ErrorException("Error while receiving a ack: "
                                 "Number of tries to receive "
                                 "the ack exceeded");
        }

        delete [] bufferArray;
    }
    LOG(1, "[SEND] Message sent");
    return true;
}

/*!
 * \brief Calculates the number of buffers necessary to encode a message
 * \return the number of buffers needed
 */
int OutgoingMessage::NbBuffers() const
{
    if (sizeData == 0)
        return 1;
    else if ((sizeData % (sizeBuffer - DATA_INDEX - SIZE_CRC)) == 0)
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC);
    else
        return sizeData/(sizeBuffer - DATA_INDEX - SIZE_CRC) + 1;
}


/*!
 * \brief Accessor to the list of buffers
 * \return list of buffers
 */
Buffer* OutgoingMessage::getListBuffer() const
{
    return (this->listBuffer); //Can throw out_of_range exception
}

/*!
 * \brief Accessor to one specific buffer
 * \param opCode operation code
 * \param sizeLeft the size left of the buffer
 * \return a buffer
 */
Buffer* OutgoingMessage::getBuffer(uint8_t opCode, uint16_t sizeLeft) const
{
    LOG(2, "getBuffer Method : ");
    LOG(2, "Buffer searched :  OPCODE = " + std::to_string(opCode)
        + " | SIZELEFT = " + std::to_string(sizeLeft));

    /* Research a buffer with the same opCode and the same sizeLeft
       in the message */
    for (int i = 0; i < NbBuffers(); i++) {
        if (listBuffer[i].getOpCode() == opCode
            && listBuffer[i].getSizeLeft() == sizeLeft) {
            LOG(1, "Buffer found \n");
            return &listBuffer[i];
        }
    }
    LOG(2, "Buffer not found \n");
    return NULL;
}

/*!
 * \brief Gets the buffers' size
 * \return the size
 */
int OutgoingMessage::getSizeBuffer() const
{
    return this->sizeBuffer;
}

/*!
 * \brief Gets the data's size
 * \return the size
 */
uint16_t OutgoingMessage::getSizeData() const
{
    return this->sizeData;
}

/*!
 * \brief Gets the operation code
 * \return the opCode
 */
uint8_t OutgoingMessage::getOpCode() const
{
    return this->opCode;
}

/*!
 * \brief Gets the device's ID
 * \return ID
 */
uint8_t OutgoingMessage::getID() const
{
    return this->idDevice;
}

/*!
 * \brief Prints for debug purposes
 * \return string
 */
std::string OutgoingMessage::toStringDebug() const
{
    std::ostringstream convert;
    convert << "---------- OutgoingMessage (DEBUG) : ----------" << std::endl;
    int n = NbBuffers();
    for (int i = 0; i < n; i++)
        convert << getListBuffer()[i].toStringDebug(i);
    convert << "---------- End OutgoingMessage (DEBUG) : ----------" << std::endl;
    return convert.str();
}
