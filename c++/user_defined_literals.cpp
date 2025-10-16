
#include <cstdio>
#include <bitset>
#include "libraries/code_helpers.h"
#include <string>

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

u64 operator""_hex( literal_string arg, unsigned long size )
{
    std::string str = std::string( arg, size + 1 );
    return std::stoll( str, nullptr, 16 );
}

u64 operator""_hex( literal_string arg )
{
    return std::stoll( std::string {arg}, nullptr, 16 );
}

using namespace std;

int
main()
{
    u32 num1 = 6_bit;
    bitset<64> reader = num1;
    printf( "num1 %s\n", reader.to_string().c_str() );

    reader = 31_bit;
    printf( "num1 %s\n", reader.to_string().c_str() );

    u64 hex_input = "0xDEADBEEF"_hex;
    printf( "hex_input %X \n", hex_input );

    u64 hex_bare = 0xDEADBEEF_hex;
    printf( "hex_bare %X \n", hex_bare );


}

void user_defined_literals() { main(); };
