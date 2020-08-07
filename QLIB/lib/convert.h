#ifndef _QLIB_CONVERT_H
#define _QLIB_CONVERT_H

/* Converts an unsigned 64 bit integer to a string.
 Supports hexadecimal, decimal, and binary conversions. */

const char *UnsignedIntegerToString(uint64 integer, char *out_result, uint32 out_result_length, INTFMT base)
{
    static char result[65];

    char *presult = result;
    uint16 value;
    uint16 place_values = 0;
    uint16 exponent = 1;

    switch(base)
    {
        case FMT_INT_BINARY:

            do
            {
                value = (uint16)(integer / Power(base, exponent));
                exponent++;
                place_values++;

            } while((value > 0) && (place_values < 64));

            while(place_values)
            {
                value = (uint16)(((integer % Power(base, place_values)) - (integer % Power(base, place_values - 1))) / Power(base, place_values - 1));

                char data = (value | 0x30);

                *presult = data;
                presult++;
                place_values--;
            }

        break;

        case FMT_INT_DECIMAL:

            do
            {
                value = (uint16)(integer / Power(base, exponent));
                exponent++;
                place_values++;

            } while((value > 0) && (place_values < 20));

            while(place_values)
            {
                value = (uint16)(((integer % Power(base, place_values)) - (integer % Power(base, place_values - 1))) / Power(base, place_values - 1));

                char data = (value | 0x30);

                *presult = data;
                presult++;
                place_values--;
            }

        break;

        case FMT_INT_HEXADECIMAL:

            do
            {
                value = (uint16)(integer / Power(base, exponent));
                exponent++;
                place_values++;

            } while((value > 0) && (place_values < 16));

            while(place_values)
            {
                value = (uint16)(((integer % Power(base, place_values)) - (integer % Power(base, place_values - 1))) / Power(base, place_values - 1));

                char data = (value | 0x30);

                if(value > 9)
                {
                    data += 7;
                }

                *presult = data;
                presult++;
                place_values--;
            }

        break;
    }

    *presult = 0;

    if(out_result)
    {
        MemoryCopy(out_result, result, out_result_length);
        return (const char *)out_result;
    }

    return (const char *)result;
}

/* Converts a signed 64 bit integer to a string.
   Supports hexadecimal, decimal, and binary conversions. */

const char *SignedIntegerToString(int64 integer, char *out_result, uint32 out_result_length, INTFMT base)
{
    static char result[66];
    char *presult = (char *)result;
    bool negative = (integer < 0);

    if(negative)
    {
        *presult++ = '-';
        integer = -integer;
    }

    UnsignedIntegerToString(integer, presult, sizeof(presult), base);

    if(out_result)
    {
        MemoryCopy(out_result, result, out_result_length);
        return (const char *)out_result;
    }

    return (char *)result;
}

const char *IntegerToString(int64 integer, char *out_result, uint32 out_result_length, INTFMT base)
{
    if(integer >= 0)
    {
        return UnsignedIntegerToString((uint64)integer, out_result, out_result_length, base);
    }

    return SignedIntegerToString(integer, out_result, out_result_length, base);
}

/* Convert double precision floating point number to a string.
   Supports only decimal conversions. */

const char *DoubleToString(double number, char *out_result, uint32 out_result_length)
{
    static char result[83];
    char *presult = result;

    bool negative = (number < 0);

    long long whole = (long long)number;
    double fraction = (number - whole);

    INTFMT format = FMT_INT_DECIMAL;

    IntegerToString(whole, presult, 20, format);

    presult += StringLength(presult);
    *presult++ = '.';
    fraction *= Power(10, 15);

    if(negative)
    {
        fraction = -fraction;
    }

    IntegerToString((long long)fraction, presult, 60, format);

    if(out_result)
    {
        MemoryCopy(out_result, result, out_result_length);
        return (const char *)out_result;
    }

    return (const char *)result;
}

/* Convert string to an unsigned 64 bit integer.
   Supports hexadecimal, decimal, and binary conversions. */

uint64 StringToUnsignedInteger(const char *str, INTFMT base)
{
    uint64 result = 0ULL;
    char *pstr = (char *)str;

    switch(base)
    {
        case FMT_INT_BINARY:
        {
            if((*pstr == '0') && (*(pstr + 1) == 'x'))
            {
                result = 0xff00ff00ff00ff00ULL;
                break;
            }

            else if((*pstr == '0') && (*(pstr + 1) == 'b'))
            {
                pstr += 2;
            }

            uint16 place_values = (uint16)StringLength(pstr);

            while(place_values)
            {
                uint8 data;

                if((*pstr <= '1') && (*pstr >= '0'))
                {
                    data = (uint8)(*pstr & 0xF);
                }

                else
                {
                    result = 0xff00ff00ff00ff00ULL;
                    break;
                }

                uint64 power = 1ULL;
                uint16 i;

                for(i = (uint16)power; i < place_values; i++)
                {
                    power *= base;
                }

                result += (uint64)(data * power);

                place_values--;
                pstr++;
            }
        }

        break;

        case FMT_INT_DECIMAL:
        {
            if((*pstr == '0') && (*(pstr + 1) == 'x'))
            {
                result = 0xff00ff00ff00ff00ULL;
                break;
            }

            else if((*pstr == '0') && (*(pstr + 1) == 'b'))
            {
                result = 0xff00ff00ff00ff00ULL;
                break;
            }

            uint16 place_values = (uint16)StringLength(pstr);

            while(place_values)
            {
                uint8 data;

                if((*pstr <= '9') && (*pstr >= '0'))
                {
                    data = (uint8)(*pstr & 0xF);
                }

                else
                {
                    result = 0xff00ff00ff00ff00ULL;
                    break;
                }

                uint64 power = 1ULL;
                uint16 i;

                for(i = (uint16)power; i < place_values; i++)
                {
                    power *= base;
                }

                result += (uint64)(data * power);

                place_values--;
                pstr++;
            }
        }

        break;

        case FMT_INT_HEXADECIMAL:
        {
            if((*pstr == '0') && (*(pstr + 1) == 'x'))
            {
                pstr += 2;
            }

            else if((*pstr == '0') && (*(pstr + 1) == 'b'))
            {
                result = 0xff00ff00ff00ff00ULL;
                break;
            }

            uint16 place_values = (uint16)StringLength(pstr);

            while(place_values)
            {
                uint8 data;

                if((*pstr <= 'f') && (*pstr >= 'A'))
                {
                    data = (uint8)((*pstr | 0x20) - 0x57);
                }

                else if((*pstr <= '9') && (*pstr >= '0'))
                {
                    data = (uint8)(*pstr & 0xF);
                }

                else
                {
                    result = 0xff00ff00ff00ff00ULL;
                    break;
                }

                uint64 power = 1ULL;
                uint16 i;

                for(i = (uint16)power; i < place_values; i++)
                {
                    power *= base;
                }

                result += (uint64)(data * power);

                place_values--;
                pstr++;
            }
        }

        break;

        default:

            result = 0xff00ff00ff00ff00ULL;

        break;
    }

    return result;
}

/* Convert string to a signed 64 bit integer.
   Supports hexadecimal, decimal, and binary conversions. */

int64 StringToInteger(const char *str, INTFMT base)
{
    int64 result = 0LL;
    char *pstr = (char *)str;
    bool negative = (*pstr == '-');

    if(negative)
    {
       result = (long long)StringToUnsignedInteger(pstr + 1, base);
       result = -result;
    }
    
    else
    {
       result = StringToUnsignedInteger(pstr, base);
    }

    return result;
}

/* Convert string to a double precision floating point.
   Supports only decimal conversions. */

double StringToDouble(const char *str) 
{
    double result = 0.0;

    char *pstr = (char *)str;

    int16 exponent = 0;
    uint16 number_of_digits = 0;
    uint16 number_of_decimals = 0;
    double power = 10.0;

    bool negative = false;
    int number;

    if(*pstr == '-')
    {
        negative = true;
        pstr++;
    }

    else if(*pstr == '+')
    {
        pstr++;
    }

    while((*pstr <= '9') && (*pstr >= '0')) 
    {
        result = result * power + (*pstr - '0');
        pstr++;
        number_of_digits++;
    }

    if(*pstr == '.') 
    {
        pstr++;

        while((*pstr <= '9') && (*pstr >= '0')) 
        {
            result = result * power + (*pstr - '0');
            pstr++;
            number_of_digits++;
            number_of_decimals++;
        }

        exponent -= number_of_decimals;
    }

    if(number_of_digits == 0) 
    {
        result = 0.0;
        return result;
    }

    if(negative) 
    {
        result = -result;
    }

    if(exponent < -307  || exponent > 1024) 
    {
        result = -1;
        return result;
    }

    number = exponent;

    if(number < 0) 
    {
        number = -number;
    }

    while(number) 
    {
        if(number & 1) 
        {
            if(exponent < 0) 
            {
               result /= power;
            } 

            else 
            {
               result *= power;
            }
        } 

        number >>= 1;
        power *= power;
    }

    return result;
}

#endif
