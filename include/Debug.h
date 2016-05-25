#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

/**
 * DEBUG print to display one message
 */
#define DEBUG(x) do { \
    if (DEBUG_TEST) { std::cerr << x << std::endl; } \
} while (0)

#endif //DEBUG_H
