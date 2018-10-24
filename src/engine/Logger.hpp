#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <cstdio>
#include <cstdarg>
#include <iostream> 
#include <iomanip>
#include <ctime>

#define logError(message, ...) (_log(stderr, this, __FUNCTION__, message, __VA_ARGS__))

#ifdef ENGINE_DEBUG
	#define log(targetStream, message, ...) (_log(targetStream, this, __FUNCTION__, message, __VA_ARGS__))
	#define logInfo(message, ...) (_log(stdout, this, __FUNCTION__, message, __VA_ARGS__))
#else
	#define log(targetStream, message, ...)
	#define logInfo(message, ...)
#endif

template <typename T>
void _log(FILE* stream, T source, const char* callerFunction, const char* message, ...) {
	va_list args;
	va_start(args, message);

	auto time = std::time(nullptr);
	auto timeLocal = *std::localtime(&time);

	std::stringstream ss;
	ss.flags(std::cout.hex | std::cout.showbase);
	ss << std::put_time(&timeLocal, "%H:%M:%S") << " " << (unsigned int) source << " " << callerFunction << "(): " << message << "\n";
	vfprintf(stream, ss.str().c_str(), args);
	va_end(args);
}
#endif