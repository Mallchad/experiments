
/** This experiment was a test to see if vtables would survive being passed
    through a generic pointer.  and the result is yes, indeed it does, atleast in
    this narrow case.
 */

#include <cstdio>

struct bird
{
    virtual void chirp()
    {
          printf("tweet tweet \n");
    };
};

struct raptor : bird
{
    void chirp() override
    {
        printf(" SQWAAAAAAAAAA \n" );
    }
};

void start()
{
    bird a;
    raptor b;

    bird* tenor = &a;
    tenor->chirp();

    tenor = &b;
    tenor->chirp();

    void* opaque = &b;
    bird* loki = static_cast<bird*>( opaque );
    loki->chirp();
}

int main()
{ start(); }
