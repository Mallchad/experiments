

#include <cstdio>
#include <chrono>

using namespace std;

#define F_CONCAT_2( x, y ) x##y
#define F_CONCAT( x, y ) F_CONCAT( x, y )

#define PRINT_SIZE( type ) printf( "size: % 3lu    type: %s \n" , sizeof( type ), #type  );

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
}
