
#include <cstdio>
#include <bitset>
#include "libraries/code_helpers.h"

using literal_integer = unsigned long long;
using literal_float = long double;
using literal_string = const char*;

// Literal that provides a number with a single zero-indexed bit position set as 1
u32 operator ""_bit(  literal_integer arg )
{ return (1 << arg); }

/** Literal that provides a number with a single zero-indexed bit position set as 1

    64-bit version */
u64 operator ""_bit64( literal_integer arg )
{ return (1 << arg); }

using namespace std;

int
main()
{
    u32 num1 = 6_bit;
    bitset<64> reader = num1;
    printf( "num1 %s\n", reader.to_string().c_str() );

    reader = 31_bit;
    printf( "num1 %s\n", reader.to_string().c_str() );
}
