
#include <cstdlib>
#include <cstdio>


void lambda_const_abuse()
{
    bool left = false;
    const int data1 = 1;
    // Compile error
    // if (left)
    // {   data1 = 1;
    // } else
    // {   data1 = 123;
    // }

    // Fine
    const int data2 = (left ? 1 : 123);

    const int data3 = [=]() {
        if (left)
        {   return 1;
        } else
        {   return 123;
        }
    } (); // call it at the end

    printf( "data1: %d \n", data1 );
    printf( "data2: %d \n", data2 );
    printf( "data3: %d \n", data3 );
}

int main()
{   lambda_const_abuse();
}
