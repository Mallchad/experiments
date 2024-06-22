#include <iostream>

using std::cout;

class base
{
public:
    base() {}
   virtual bool pure(int a) = 0;
   virtual ~base() {};
};

class derived final : base
{
public:
    int x;

    derived() { int i = 0;}
    bool pure(int in) override {return bool(x);}
    bool no_vtable(int in) { return bool(x); }
    //void pure(void) {}
    ~derived() {  }
};

class normal final
{
public:
    int x;
    bool pure(int a) { return bool(x); }
};

// bool
//derived::pure(int a)  {return true;}

struct data
{
    int x;
};

bool actual_pure(int in)
{
    return bool(in);
}

int main()
{
    derived* ptr_a = new derived();
    derived a;
    normal b;
    data c;
    ptr_a->x = 69;
    cout << ptr_a->pure(1) << std::endl;

    std::cin >> a.x;
    cout << a.pure(1) << std::endl;
    std::cin >> a.x;
    cout << a.no_vtable(1) << std::endl;
    std::cin >> b.x;
    cout << b.pure(1) << std::endl;
    std::cin >> b.x;
    cout << actual_pure(c.x) << std::endl;

    cout << "is 'a' polymorphic? " << std::is_polymorphic<decltype(a)>::value << std::endl;
    cout << "is 'b' polymorphic? " << std::is_polymorphic<decltype(b)>::value << std::endl;
    cout << "is 'c' polymorphic? " << std::is_polymorphic<decltype(c)>::value << std::endl;
    cout << "is 'ptr_a' polymorphic? " << std::is_polymorphic<decltype((derived)(*ptr_a))>::value << std::endl;
}
