
#include <iostream>
#include <memory.h>
#include <string.h>

void pause()
{
    int a;
    std::cin >> a;
}

int main()
{
    long buffer_size = 1'000'000;
    long big_size =  100'000'000;
    unsigned char buffer[ buffer_size ];
    void* heap_buffer = malloc( big_size );
    pause();
    int random;
    std::cin >> random;
    memset(buffer, random, buffer_size);
    memset(heap_buffer, random, big_size);
    pause();
    std::cout << sizeof buffer << buffer[500] << ((char*)heap_buffer)[500];
}
