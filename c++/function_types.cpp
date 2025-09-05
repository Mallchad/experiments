/** In this file is laid our a bunch of different ways you can declare function
 * types, function pointers, and everything under it, lambdas, closures, etc. .*/

#include <functional>

void callback(int) {}

int main()
{
    // Auto-deduce type
    std::function func1 = callback;
    // Use function signature void foo(int)
    std::function<void(int)> func2 = callback;

    // use function signature from known function
    using callback_type = decltype(callback); // type alias
    std::function<callback_type> func3 = callback;

    // C style
    typedef void(*callback_t)(int); // type alias
    callback_t func4 = callback;
    void(*func5)(int) = callback; // variable decleration

    // C++-style
    using callback_t2 = void(*)(int); // type alias
    callback_t2 func7 = callback;
    void(*func8)(int) = callback; // variable delceration

    // Lambda capture
    std::function<void()> func9 = []()
    {
         callback(1);
    };
}
