#ifndef _MATH_H
#define _MATH_H

// Returns the value of unsigned integer {base} raised to the power of {exponent}

long long Power(long long base, long long exponent)
{
    long long result = 1LL;

    while(exponent)
    {
        if(exponent & 1) 
        {
            result *= base;
        }

        exponent >>= 1;
        base *= base;
    }
    
   if(result == 0LL) --result;
   return result;
}

#endif
