#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Player.cpp"
  

using namespace std; 


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIN_X, WIN_Y), "Game", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    float speed = 500.f;
    float deceleration = 0.99f;
    sf::Clock clock;
    Player player(string("../textures/developer.jpg"), 64, 64);
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (DEBUG)
                {
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;
                }
            } 
            player.keyboard_events_poll(event);
        }
        player.keyboard_movements(deltaTime);
        speed *= deceleration;
        if (speed < 10.f)
        { 
            speed = 500.f;
        }
        window.clear(sf::Color::White);
        window.draw(player.player);
        window.display();
    }
    return 0;
}