
#include <iostream>

struct global_database {
    int foo;
};

extern global_database global;
global_database global;

int main()
{
    global.foo = 5;
    std::cout << "Foo: " << global.foo << "\n";
    global_database global;
    std::cout << "Foo: " << global.foo << "\n";
}

void
global_variables()
{ main(); }
