#include "strutils.h"

bool str_reverse(const char* str, char* buf)
{
    if (str == NULL) return false;

    int len = strlen(str);
    if (len == 0) return true;

    for (int i = 0; i < len; i++)
    {
        buf[i] = str[len - i - 1];
    }

    buf[len] = '\0';

    return true;
}

bool str_trim(const char* str, char* buf)
{
    if (str == NULL) return false;

    int left_string = 0;

    int len = strlen(str);
    if (len == 0)
    {
        buf[len] = '\0';
        return false;
    }

    int right_string = len - 1;

    while (left_string < len && isspace((unsigned char)str[left_string]))
    {
        left_string++;
    }

    while (left_string <= right_string &&
           isspace((unsigned char)str[right_string]))
    {
        right_string--;
    }

    int trimmed_len = right_string - left_string + 1;

    memmove(buf, str + left_string, trimmed_len);

    buf[trimmed_len] = '\0';

    return true;
}

bool str_to_int(const char* str, int* num)
{
    *num = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 48 && str[i] <= 57)
        {
            *num = *num * 10 + (str[i] - '0');
        }
        else
        {
            return false;
        }
    }

    return true;
}