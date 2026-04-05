
#include <string>
#include <vector>
#include <format>
#include <thread>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define print_q( STR_ ) printf( STR_ );
#define print_q( STR_ ) printf( STR_ );

#define print( FORMAT_, ... ) printf( "%s", std::format( FORMAT_, __VA_ARGS__ ) );
#define println( FORMAT_, ... ) printf( "%s\n", std::format( FORMAT_, __VA_ARGS__ ) );

// -- Redirectable typedefs --
using fint8   = int8_t;
using fint16  = int16_t;
using fint32  = int32_t;
using fint64  = int64_t;

using fuint8  = uint8_t;
using fuint16 = uint16_t;
using fuint32 = uint32_t;
using fuint64 = uint64_t;

using i8   = int8_t;
using i16  = int16_t;
using i32  = int32_t;
using i64  = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
// struct u40 { u8 d[5]; };
using u64 = uint64_t;
// struct u128 { u64 d[2]; };
// struct u256 { u64 d[4]; };
// struct u512 { u64 d[8]; };
// struct u1024 { u64 d[16]; };
// struct u2048 { u64 d[32]; };
// struct u4096 { u64 d[64]; };

// Fixed width floats only supported
using f32 = float;
using f64 = double;

using byte = u8;
using fbyte = u8;
using usize = u64;
using isize = i64;

// String types
using fstring = std::basic_string<char>;
using fstring_view = std::basic_string_view<char>;
using cstring = const char*;
// using fpath = std::filesystem::path;


// Platform specific setup

#ifdef _WIN32
    #include <windows.h>
    #include <fcntl.h>
    #include <io.h>

    #include <conio.h>

#elif defined(__linux__)
    #include <unistd.h>
    #include <fcntl.h>
    #include <termios.h>
#endif

using namespace std;
using namespace std::chrono_literals;

static bool exit_ready = false;
string input;
std::vector<char> buf;

#if 0
#include <iostream>

// All blocking. all of it
void iostream_attempt()
{
        // Blocks
        // cin.getline( buf.data(), 100 );

        // NOTE: Always returns 0 on some platforms (useless)
        // long count = cin.readsome( buf.data(), 1 );
        // print("# %d ", count );

        // Also blocks, but until you fulfil the character requirement, not just getline
        // cin.read( buf, 1 );

        /** NOTE: Breaks if two newlines are input, so we have to clear the newlines in a loop..
            NOTE: This is horrible API design and I hate whoever designed this.
            NOTE: BUT IT DOES WORK, it IS non-blocking */


        cin.get( buf.data(), 2, '\0' );
        // cin.ignore( 1000 );
        if (cin.peek() == '\n')
        {
            cin.get( buf.data(), 2, '\0' );
        }

        // { cin.ignore( 10003, '\n' ); }

        input = buf.data();
        print( "ASCII Character {}   Size: {} Peek: {} {}\n", int(buf[0]), input.size(),
               char(cin.peek()), int(cin.peek()) );
        print_q( "#" );
        fflush( stdout );
        if (cin.fail())
        {   print_q( "Failed" );
        }
        if (cin.bad())
        {   print_q( "Bad" );
        }
        // fflush( stdin );

        // if (input == "\n")
        // {
        //     print( "Waiting for new input: " );
        //     cin.getline( buf.data(), 1024 );
        //     while (cin.peek() == '\n')
        //     { cin.ignore( 1000, '\n' ); }
        // }

        if (input.size())
        {   println( "Echo Input: '{}'", input );

            if (input == "exit")
            {   exit_ready = true;
            }
        }
}
#else
void iostream_attempt() {}
#endif

#ifdef __linux__
bool console_input_available()
{
    // char _stub;
    // return read( STDIN_FILENO, &_stub, 1 ) > 0;
    return true;
}

bool console_platform_init()
{
    struct termios ttystate;
    tcgetattr( STDIN_FILENO, &ttystate );
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &ttystate );

    int flags = fcntl( STDIN_FILENO, F_GETFL, 0 );
    fcntl( STDIN_FILENO, F_SETFL, flags | O_NONBLOCK );
    return true;
}
#elif defined(_WIN32)
void windows_fix_console()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    i32 consoleHandleR, consoleHandleW;
    u64 stdioHandle;
    FILE *fptr;

    // Creates a new console window if one wasn't open already
    AllocConsole();
    fstring console_name = "VMEC Logging Console";
    SetConsoleTitleA( console_name.c_str() );

    EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE , MF_GRAYED);
    DrawMenuBar(GetConsoleWindow());

    GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo );

    stdioHandle = (u64)GetStdHandle( STD_INPUT_HANDLE );
    consoleHandleR = _open_osfhandle( stdioHandle, _O_TEXT );
    fptr = _fdopen( consoleHandleR, "r" );
    *stdin = *fptr;
    setvbuf( stdin, nullptr, _IONBF, 0 );

    stdioHandle = (u64)GetStdHandle( STD_OUTPUT_HANDLE );
    auto wstdout = stdioHandle;
    (void)( wstdout );
    consoleHandleW = _open_osfhandle( stdioHandle, _O_TEXT );
    fptr = _fdopen( consoleHandleW, "w" );
    *stdout = *fptr;
    setvbuf( stdout, nullptr, _IONBF, 0 );

    stdioHandle = (u64)GetStdHandle( STD_ERROR_HANDLE );
    *stderr = *fptr;
    setvbuf( stderr, nullptr, _IONBF, 0 );

    // Enable ANSI 256 color processing on normal Command Prompt Window
    HANDLE win32_stdout = GetStdHandle( STD_OUTPUT_HANDLE );
    HANDLE win32_stdin = GetStdHandle( STD_INPUT_HANDLE );
    auto err = SetConsoleMode( win32_stdout, ENABLE_VIRTUAL_TERMINAL_PROCESSING | ENABLE_PROCESSED_OUTPUT );
    auto err2 = SetConsoleMode( win32_stdin, ENABLE_VIRTUAL_TERMINAL_INPUT );
    /* Tell the console not to interpret the input stream for unicode, take
       it verbatim _O_U8TEXT or _O_U16TEXT is an option but requires
       rewriting of the console output facilities. */
    _setmode( _fileno(stdin), _O_BINARY );
    _setmode( _fileno(stdout), _O_BINARY );
    /* Enable UTF-8 however. This is irrelevant in proper _O_U8TEXT mode or
       simiar. But convenient for unformatted UTF-8 unicode strings */
    SetConsoleOutputCP( 65001 ); // CP_UTF8

}

bool console_input_available()
{
    return (_kbhit() != 0);
}

bool console_platform_init() 
{ 
    windows_fix_console();
    return true; 
}
#endif

void platform_c_attempt()
{
    if (console_input_available())
    {
        fgets( buf.data(), 100, stdin );
        // NOTE: Not needed
        // NOTE: Extremely slow compared to fgets.
        // int read_bytes = read( STDIN_FILENO, buf.data(), 100 );

        input += buf.data();
    }

    // print( "Echo: {}", input );
    // print( "\033[1F" );
    // print( "\033[2K" );
    print( "Echo: {} ASCII: {}", input.back(), int(input.back()) );
    // print( "\033[1E" );

    print_q( "\033[0E" );
    print_q( "\033[2K" );
    print( "{}", input );

    bool do_backspace = (input.back() == 127);
    if (do_backspace)
    {   // Take off the backspace + 1 character
        bool short_string_special_case = (input.size() < 2);
        size_t new_size = (short_string_special_case ? 0 : (input.size() - 2));
        input.resize( new_size );
    }
    else if (input.back() == 10)
    {
        println( "Input Submitted: {}", input );
        input.clear();
    }
}

int main()
{
    buf.resize( 1024 );
    console_platform_init();

    while (exit_ready == false)
    {
        memset( buf.data(), 0, buf.size() );

        iostream_attempt();
        platform_c_attempt();
        std::this_thread::sleep_for( 16.6ms );
    }
}
