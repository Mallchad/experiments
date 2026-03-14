
#include <string>
#include <memory>
#include <cstdio>
#include <thread>
using namespace std;

void thread_pointer( int* a )
{
    *a = 69;
}

void thread_double_pointer( int** a )
{
    *a = new int;
}

void thread_ref( int& a )
{
}
void thread_ref_pointer( int* & a )
{
    a = new int;
}

int main()
{
    int* a = new int;
    int* b = nullptr;
    int c;
    int* d = nullptr;
    auto thread1 = std::thread( thread_pointer, a );
    auto thread2 = std::thread( thread_double_pointer, &b );
    // broken because of std::thread requriements
    // auto thread3 = std::thread( thread_ref, c );
    auto thread3 = std::thread( thread_ref, std::ref(c) );
    // crash d not set yet
    // d = 69;
    auto thread4 = std::thread( thread_ref_pointer, std::ref(d) );
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
}
