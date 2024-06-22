
#include <chrono>
#include <iostream>
#include <cstring>

template <typename... t>
void print(t... vargs)
{
    (std::cout << ... << vargs )  << "\n";
}

template <typename t_duration>
float get_seconds( t_duration target )
{
    return std::chrono::duration_cast< std::chrono::duration<float>
                                       >( target ).count();
}

struct padded
{
    bool u = 0; int x = 0;
    int get_x() { return x; };
    int get_const_x() const { return x; };
    constexpr int get_immediate_x() const { return x; };
};

int main()
{
    int* buffer1 = new int[100'000'000];
    int* buffer2 = new int[100'000'000];
    int* buffer3 = new int[100'000'000];

    padded* buffer_padded = new padded[100'000'000];


    auto stamp = std::chrono::steady_clock::now();

    for (int i=0; i<100'000'000; ++i)
    {
        buffer1[i] = buffer2[i];
    }
    auto time_linear = get_seconds( std::chrono::steady_clock::now() - stamp);

    stamp = std::chrono::steady_clock::now();
    for (int i=0; i<100'000'000; ++i)
    {
        buffer3[i] = buffer_padded[i].x;
    }
    auto time_objectified = get_seconds( std::chrono::steady_clock::now() - stamp );

    stamp = std::chrono::steady_clock::now();
    for (int i=0; i<100'000'000; ++i)
    {
        buffer3[i] = buffer_padded[i].get_x();
    }
    auto time_private = get_seconds( std::chrono::steady_clock::now() - stamp );

    stamp = std::chrono::steady_clock::now();
    for (int i=0; i<100'000'000; ++i)
    {
        buffer3[i] = buffer_padded[i].get_const_x();
    }
    auto time_const = get_seconds( std::chrono::steady_clock::now() - stamp );

    stamp = std::chrono::steady_clock::now();
    for (int i=0; i<100'000'000; ++i)
    {
        buffer3[i] = buffer_padded[i].get_immediate_x();
    }
    auto time_immediate = get_seconds( std::chrono::steady_clock::now() - stamp );

    stamp = std::chrono::steady_clock::now();
    std::memcpy( buffer3, buffer1, 100'000'000*sizeof(int));
    auto time_memcpy = get_seconds( std::chrono::steady_clock::now() - stamp );


    print( "time_linear: ", time_linear ) ;
    print( "time_objectified: ", time_objectified );
    print( "time_private: ", time_private );
    print( "time_const: ", time_const );
    print( "time_immediate: ", time_immediate );
    print( "time_memcpy: ", time_memcpy );

    delete[] buffer1;
    delete[] buffer2;
    delete[] buffer3;
    delete[] buffer_padded;
}
