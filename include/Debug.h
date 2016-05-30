#ifndef DEBUG_H
#define DEBUG_H


#define LOG_LEVEL 0

#ifndef LOG_LEVEL
#define LOG_LEVEL 0
#endif

/**
 * @brief DEBUG print to display one message
 */
#define LOG(level, x) do {                                              \
        if (LOG_LEVEL && (level >= LOG_LEVEL)) { std::cerr << "\033[1;34m" << x << " \033[0m" << std::endl; } } while (0)

#endif //DEBUG_H
