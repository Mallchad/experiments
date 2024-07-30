

#include <cmath>
#include <iostream>

int main()
{
    float random_float;
    std::cin >> random_float;
    bool sign = *(int*)(&random_float) & (1 << 31);
    std::cout << sign;

    std::cin >> random_float;
    if (random_float > 0.0f) { sign = 0; }
    else { sign = 1; }
    std::cout << sign;

    std::cin >> random_float;
    sign = std::signbit(random_float);
    std::cout << sign;

}
