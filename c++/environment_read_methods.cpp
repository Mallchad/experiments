
#include <unistd.h>
#include <iostream>

int main( int argc, char** argv, char** env )
{
    std::cout << (environ[0]) << "\n";
    std::cout << (env[0]) << "\n";
}
