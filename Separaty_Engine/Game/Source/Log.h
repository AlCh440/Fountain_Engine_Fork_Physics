#ifndef __LOG_H__
#define __LOG_H__

#define DEBUG_LOG(format, ...) Log(__FILE__, __LINE__, format, __VA_ARGS__)

char* Log(const char file[], int line, const char* format, ...);

#endif  // __LOG_H__