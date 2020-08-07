#ifndef _QLIB_STRINGS_H
#define _QLIB_STRINGS_H

/* Copies a string from one memory location to an other memory location. */

uint32 CopyString(cstring to, cstring from, uint32 length)
{
    uint32 bytes_copied = 0;

    while(bytes_copied < length)
    {
        uint8 byte = (to[bytes_copied] = from[bytes_copied]);
        ++bytes_copied;

        if(!byte) break;
    }

    return bytes_copied;
}

/* Find length of string. Rewrite of libc strlen(). */

uint32 StringLength(const cstring str)
{
    uint32 length = 0;
    cstring pstr = (cstring)str;

    while(*pstr)
    {
        ++length;
        pstr++;
    }

    return length;
}

/* Checks equality of two c-strings. */

bool StringCompare(const cstring string_a, const cstring string_b, bool case_sensitive)
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

/* Finds first occurrence of a string within another string. Returns the index into the string or zero if non existent. */

int32 FindFirstOccurrenceOfString(const cstring haystack, const cstring needle, bool case_sensitive)
{
    int32 index = 0;
    uint32 needle_length = StringLength(needle);
    uint32 haystack_length = StringLength(haystack);

    if(haystack_length > 2048)
    {
        return -1; 
    }

    if(needle_length > haystack_length)
    {
        return -1; 
    }

    while(index < haystack_length)
    {
        uint32 len = StringLength(haystack);
        char haystack_section[len + 1];
        CopyString((cstring)haystack_section, (cstring)haystack, len);
        haystack_section[needle_length] = 0;

        if(StringCompare(haystack_section, needle, case_sensitive))
        {
            return index; 
        }

        index++;
        haystack++;
    }

    return 0; 
}

/* Checks if a string is a decimal. */

bool IsDecimal(const cstring str)
{
    bool numeric = (str) ? true : false;
    cstring tmpstr = (cstring)str;
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
