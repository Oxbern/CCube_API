#ifndef DEBUG_H
#define DEBUG_H


#define LOG_LEVEL 1

#ifndef LOG_LEVEL
    #define LOG_LEVEL 0
#endif

/**
 * DEBUG print to display one message
 */
#define LOG(level, x) do { \
if (LOG_LEVEL && (LOG_LEVEL >= level)) { std::cerr << x << std::endl; } } while (0)

#endif //DEBUG_H
