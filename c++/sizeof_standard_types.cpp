

#include <cstdio>
#include <cstdint>

#include <chrono>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;

#define F_CONCAT_2( x, y ) x##y
#define F_CONCAT( x, y ) F_CONCAT( x, y )

#define PRINT_SIZE( type ) printf( "size: % 3lu    type: %s \n" , sizeof( type ), #type  );

using i8   = int8_t;
using i16  = int16_t;
using i32  = int32_t;
using i64  = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
// struct u40 { u8 d[5]; };
using u64 = uint64_t;

struct u40 { u8 d[5]; };
using u64 = uint64_t;
struct u128
{
    u64 d[2] = {};
    constexpr u128() = default;
    constexpr u128( u64 low, u64 high )
    { d[0] = low; d[1] = high; }
};
struct u256 { u64 d[4]; };
struct u512 { u64 d[8]; };
struct u1024 { u64 d[16]; };
struct u2048 { u64 d[32]; };
struct u4096 { u64 d[64]; };

struct uid
{
    i64 id;
    u128 uuid;
};

int main()
{
    PRINT_SIZE( char );
    PRINT_SIZE( int );
    PRINT_SIZE( long );
    PRINT_SIZE( long long );
    PRINT_SIZE( float );
    PRINT_SIZE( double );
    PRINT_SIZE( long double );
    PRINT_SIZE( chrono::time_point<chrono::system_clock> );
    PRINT_SIZE( uid );
    PRINT_SIZE( vector<int> );
    PRINT_SIZE( vector<uid> );
    PRINT_SIZE( string );
    PRINT_SIZE( filesystem::path );
}
