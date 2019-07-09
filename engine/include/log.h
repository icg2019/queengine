
#ifndef LOG_H
#define LOG_H


#include <iostream>
#include <cstdlib>

/* In the release version define NDEBUG macro */
// #define NDEBUG  // Clears out the DEBUG macro
// #define NWARN   // Clears out the WARN macro
// #define NASSERT // Clears out the ASSERT macro
// #define NINFO   // Clears out the INFO macro
// #define NERROR  // Clears out the ERROR macro

#ifndef NINFO
#   define INFO(...) \
	std::cout << "[INFO] " << __VA_ARGS__ << std::endl;
#else
#   define INFO(...)
#endif

#ifndef NWARN
#   define WARN(...) \
	std::cout << "[WARN] " << __VA_ARGS__ << std::endl;
#else
#   define WARN(...)
#endif

#ifndef NERROR
#   define ERROR(...)							      \
	do {									  \
		std::cout	<< "[ERROR] " << __FILE__ << " line " << __LINE__	    \
				<< std::endl << __VA_ARGS__ << std::endl;		    \
		std::exit(EXIT_FAILURE);					      \
	} while(false)
#else
#   define ERROR(...)
#endif

#ifndef DEBUG
    #ifndef NDEBUG
    #   define DEBUG(...) \
	std::cerr << "[DEBUG] " << __VA_ARGS__ << std::endl;
    #else
    #   define DEBUG(...)
    #endif
#endif


#ifndef NASSERT
#   define ASSERT(condition, ...) \
	do { \
		if(!(condition)){ \
			std::cerr	<< "Assertion `" # condition "` failed in " << __FILE__	\
					<< " line " << __LINE__ << ": " << __VA_ARGS__ << std::endl; \
			std::exit(EXIT_FAILURE); \
		} \
	} while(false)
#else
#   define ASSERT(condition, ...)
#endif

#endif