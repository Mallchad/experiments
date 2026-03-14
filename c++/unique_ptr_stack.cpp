

#include <string>
#include <memory>
#include <cstdio>
using namespace std;

int main()
{
    alignas(64) char buffer[1024];
    std::string hello = "Hello world!";
    unique_ptr<string> ref_hello { new(buffer) std::string {"Hello World!" } };
    printf( "%s \n", ref_hello->c_str() );

    unique_ptr<string> ref_hello2 = std::move( ref_hello );
    printf( "%s \n", ref_hello2->c_str() );
    ref_hello2.release();
}
