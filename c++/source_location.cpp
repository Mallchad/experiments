
#include <cstdio>
#include <source_location>

using i64 = long long;
using cstring = const char*;
#define PROC auto
namespace tyon {
struct source_location
{
    i64 line_n = 0;
    i64 column_n = 0;
    cstring filename;
    cstring function_signature;

    constexpr PROC line() -> i64 { return line_n; }
    constexpr PROC column() -> i64 { return column_n; }
    constexpr PROC file_name() -> cstring { return filename; }
    constexpr PROC function_name() -> cstring { return function_signature; }
};
}

#ifdef __GNUC__
    #define TYON_SOURCE_LOCATION() ::tyon::source_location { __LINE__, 0, __FILE__, __PRETTY_FUNCTION__ }
#else
    #define TYON_SOURCE_LOCATION() ::tyon::source_location { __LINE__, 0, __FILE__, __func__ }
#endif // __GNUC__
struct foo
{

    int one;
    int two;

    std::source_location location = std::source_location::current();
};

void print_location( std::source_location arg )
{
    printf( "source location: %s %s %d %d \n ",
            arg.file_name(), arg.function_name(), arg.line(), arg.column() );
}

void print_tyon_location( tyon::source_location arg )
{
    printf( "tyon source location: %s %s %d %d \n ",
            arg.file_name(), arg.function_name(), arg.line(), arg.column() );
}

void source_location()
{
    foo var1;
    print_location( var1.location );
    print_location( std::source_location::current() );
}

int main()
{
    source_location();
    printf( "%s \n", __PRETTY_FUNCTION__ );
    printf( "%s \n", __func__  );
    print_location( std::source_location::current() );
    print_tyon_location( TYON_SOURCE_LOCATION() );

}
