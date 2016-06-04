#ifndef DEBUG_H
#define DEBUG_H

/*!
 * \file Debug.h
 * \brief Please change LOG_LEVEL to print debug messages
 * \version 0.1
 */

/*!
 * \def LOG_LEVEL
 * \brief defines the level of debug desired
 */
#define LOG_LEVEL 0

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

/*!
 * \def LOG(level, x)
 * \brief DEBUG print to display one message
 */
#define LOG(level, x) do {                                              \
        if (LOG_LEVEL && (level >= LOG_LEVEL)) { std::cerr << "\033[1;34m" << x << " \033[0m" << std::endl; } } while (0)

#endif //DEBUG_H
