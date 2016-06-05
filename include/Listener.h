#ifndef LISTENER_H
#define LISTENER_H

/*!
 * \file Listener.h
 * \brief TODO
 * \version 0.1
 */

class Controller; //Needed to avoid recursive includes

/*!
 * \class Listener
 * \brief TODO
 */
class Listener
{
 public:
    /*!
     * \fn virtual void onInit(Controller & c)
     * \brief TODO
     * \param c controller
     */
    virtual void onInit(Controller & c);

    /*!
     * \fn virtual void onConnect(Controller &c)
     * \brief TODO
     * \param c controller
     */
    virtual void onConnect(Controller &c);

    /*!
     * \fn virtual void onDisconnect(Controller &c)
     * \brief TODO
     * \param c controller
     */
    virtual void onDisconnect(Controller &c);

    /*!
     * \fn virtual void onData(Controller &c)
     * \brief TODO
     * \param c controller
     */
    virtual void onData(Controller &c);

    /*!
     * \fn virtual void onDeviceChange(Controller &c)
     * \brief TODO
     * \param c controller
     */
    virtual void onDeviceChange(Controller &c);

    /*!
     * \fn virtual void onExit(Controller &c)
     * \brief TODO
     * \param c controller
     */
    virtual void onExit(Controller &c);
};

#endif //LISTENER_H
