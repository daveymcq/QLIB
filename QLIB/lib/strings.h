#ifndef _QLIB_STRINGS_H
#define _QLIB_STRINGS_H

// Copies a string from one memory location to an other memory location.

uint32 CopyString(char *to, char *from, uint32 length)
{
    uint32 bytes_copied = 0;

    while(bytes_copied < length)
    {
        char byte = (to[bytes_copied] = from[bytes_copied]);
        ++bytes_copied;

        if(!byte) break;
    }

    return bytes_copied;
}

// Find length of string.

uint32 StringLength(const char *str)
{
    uint32 length = 0;
    char *pstr = (char *)str;

    while(*pstr)
    {
        ++length;
        pstr++;
    }

    return length;
}

// Checks equality of two c-strings.

bool StringCompare(const char *string_a, const char *string_b, bool case_sensitive)
{
    bool result;

    if(result = (StringLength(string_a) == StringLength(string_b)))
    {
        uint32 offset;
        
        for(offset = 0; result && (offset < StringLength(string_a)); offset++)
        {
            result = (string_a[offset] == string_b[offset]);
            if(!result && !case_sensitive) result = ((string_a[offset] | 0x20) == (string_b[offset] | 0x20));
        }
    }

    return result;
}

// Checks if a string is a decimal.

bool IsDecimal(const char *str)
{
    bool numeric = (str) ? true : false;
    char *tmpstr = (char *)str;
    uint32 index = 0;

    while((*tmpstr) && (numeric))
    {
        numeric = (((*tmpstr >= '0') && (*tmpstr <= '9')) ||
                   ((index == 0) && (*tmpstr == '-')) ||
                   ((*tmpstr == '.')));

        index++;
        tmpstr++;
    }

    return numeric;
}

#endif
