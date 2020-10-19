#ifndef _QLIB_TYPES_H
#define _QLIB_TYPES_H

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned long long

#define int8 char
#define int16 short
#define int32 int
#define int64 long long

#if defined(_MSC_VER)
    #if (_MSC_VER >= 1400)
        #define uint64 __uint64
        #define int64 __int64
    #endif
#endif

#define cstring char *

#ifndef bool
    #define bool unsigned char
#endif

#ifndef true
    #define true 0x01
#endif

#ifndef false
    #define false 0x00
#endif

#ifdef BIT
    #undef BIT
#endif

#ifdef bit
    #undef bit
#endif

#ifdef BYTE
    #undef BYTE
#endif

#ifdef byte
    #undef byte
#endif


typedef enum _INTFMT
{
    FMT_INT_BINARY = 2,
    FMT_INT_DECIMAL = 10,
    FMT_INT_HEXADECIMAL = 16

} INTFMT;

#pragma pack(push, 1)

typedef struct _BIT
{
    bool value : 1; 

} QBIT, qbit;

typedef union _BYTE
{
    struct _BITS
    {
        bool bit_1 : 1;
        bool bit_2 : 1;
        bool bit_3 : 1;
        bool bit_4 : 1;
        bool bit_5 : 1;
        bool bit_6 : 1;
        bool bit_7 : 1;
        bool bit_8 : 1;

    } bits;

    int8 value;

} QBYTE, qbyte;

#define BIT QBIT
#define bit qbit

#define BYTE QBYTE
#define byte qbyte

#pragma pack(pop)

#endif
