#include <iostream>
#include <typeinfo>


int size(int arr[]) { return sizeof(arr); }
int main()
{
    using namespace std::chrono_literals;
    int arr[100]; arr[1] = size(arr);
}
