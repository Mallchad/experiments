
/**
This is a demonstration of union initialization behaviour in C23 and GCC 15 release changes.
https://gcc.gnu.org/gcc-15/changes.html

In this change it was decided that only the first union 'member' would be zero'd,
not all of them. To test I have written a small program compiled with '-std=c23'.

When reading uninitialized memory the behaviour is considered 'Undefined
Behaviour', ie anything can happen. This makes testing it quite difficult
because sometimes the value will be sensible, 0, sometimes it will be weird
0xDEADBEEF, and sometimes it will be completely random.

To test this a large amount of random data has been streamed into the
stack. When testing it will found that gcc is relatively unwilling to 'pop' the
stack in the middle of a function if it doens't need to, so it was necessary to
split the stack tainting and union use into seperate functions, then it is
rather willing to pop the stack between functions.

Different optimization levels will encourage different results with varying
amount of random numbers being left in the union, you are encouraged to
experiment with compiler settings to see what changes it. As well as non GCC 15
changes.

At different optimization levels the optimizer will be tempted to delete various
sections of code where it wouldn't be able to in a real program. As always the
use of random numbers combined with standard output and file writing is
reccomended to 'deoptimize' the program in strategic places

Example invocation
$ gcc -O0 gcc15_union_initialization.c -o build/gcc_union_initialization ; build/gcc_union_initialization

*/

#include <stdio.h>
#include <stdlib.h>

typedef union Foo {
    int a;
    long long b;
} Foo;

void
taint_the_stack()
{
    enum{ size = 1123123 };

    /** Okay APARENTLY const in C is different to C++ and has external linkage
        This has the side effect of turning arrays into VALs which can't be optimized correctly
        FML. This made testing SO HARD */
    //static const int size = 1123123;

    int garbage_generator[size];
    for (int i=0; i<size; ++i)
    {
        garbage_generator[i] = rand();
    }
    printf( "deoptimization %d %d %d \n",
    garbage_generator[123], garbage_generator[10000], garbage_generator[ 1000000 ] );
    printf( "&garbage: %x &garbage_last: %x \n", &garbage_generator, &(garbage_generator[size-1]) );
}

void
use_stack()
{

    Foo foo_one = {0};
    long long ub_read = foo_one.b;
    Foo foos[2];

    printf( "&foo_one: %x, &foos: %x \n", &foo_one, &foos );
    printf( "foo_one: %d | %ld \n", foo_one.a, foo_one.b );
    printf( "foo [0]: %d | %ld \n", foos[0].a, foos[0].b );
    printf( "foo [1]: %d | %ld \n", foos[1].a, foos[1].b );
   printf( "ub_read: %d \n", ub_read );
}

int main()
{
    taint_the_stack();
    use_stack();
    taint_the_stack();
    fflush( stdout );

}
