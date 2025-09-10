#ifndef _STRUTILS_H_
#define _STRUTILS_H_

#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool str_reverse(const char* str, char* buf);
bool str_trim(const char* str, char* buf);
bool str_to_int(const char* str, int* num);

#endif