
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
int main()
{
    try
    {
        sf::Window window(
            sf::VideoMode(640, 480),
            "Hello World");

        while (window.isOpen())
        {
            window.display();
        }
        window.close();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
    }

    return 0;
}
