#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Utils.cpp"
#include "Keys.cpp"

using namespace std;


class Player
{
private:

    void is_behind_map()
    {
        sf::FloatRect bounds = player.getGlobalBounds();
        sf::Vector2f playerPosition = player.getPosition();
        if (DEBUG) {
            cout << "TOP: " << bounds.top << " LEFT: " << bounds.left << " WIDTH: " << bounds.width << " HEIGHT: " << bounds.height << endl;
        }
        float boundsLeft = bounds.left;
        float boundsTop = bounds.top;

        const float distance = 40;

        // ушел за левую часть
        if (boundsLeft <= -distance)
        {
            player.setPosition(sf::Vector2f(static_cast<float>(WIN_X) - (distance * 2.5f), playerPosition.y));
        }

        // ушел за правую часть
        if (boundsLeft + bounds.width >= static_cast<float>(WIN_X)) 
        {
            player.setPosition(sf::Vector2f(0.f, playerPosition.y));
        }

        // Ушел вверх 
        if (boundsTop <= -distance)
        {
            player.setPosition(sf::Vector2f(playerPosition.x, static_cast<float>(WIN_Y)));
        }

        // ушел вниз 
        if (boundsTop > static_cast<float>(WIN_Y))
        {
            player.setPosition(sf::Vector2f(playerPosition.x, 0.f));
        }
    }

    float calculate_smooth_movement(float deltatime, float direction, float speed)
    {
        return direction * speed * deltatime;
    }

public:
    sf::Sprite player;
    sf::Texture texture;
    sf::Vector2f velocity;

    const unsigned int speed = 800;

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;
    bool rotateRight = false;
    bool rotateLeft = false;

    void keyboard_events_poll(sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (DEBUG) {
                cout << "KEY CODE: " << event.key.scancode << endl;
            }
            if (event.key.scancode == Keys::w)
            {
                movingDown = true;
            }
            if (event.key.scancode == Keys::s)
            {
                movingUp = true;
            }
            if (event.key.scancode == Keys::a)
            {
                movingLeft = true;
            }
            if (event.key.scancode == Keys::d)
            {
                movingRight = true;
            }
            if (event.key.scancode == Keys::q)
            {
                rotateLeft = true;
            }
            if (event.key.scancode == Keys::e)
            {
                rotateRight = true;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.scancode == Keys::w)
            {
                movingDown = false;
            }
            if (event.key.scancode == Keys::s)
            {
                movingUp = false;
            }
            if (event.key.scancode == Keys::a)
            {
                movingLeft = false;
            }
            if (event.key.scancode == Keys::d)
            {
                movingRight = false;
            }
            if (event.key.scancode == Keys::q)
            {
                rotateLeft = false;
            }
            if (event.key.scancode == Keys::e)
            {
                rotateRight = false;
            }
        }
    }

    void keyboard_movements(float deltaTime)
    {
        if (rotateLeft)
        {
            rotate(deltaTime, 1);
        }
        if (rotateRight)
        {
            rotate(deltaTime, -1);
        }
        if (movingUp)
        {
            move_forward(deltaTime, -1);
        }
        if (movingDown)
        {
            move_forward(deltaTime, 1);
        }
        if (movingLeft)
        {
            move_left_and_right(deltaTime, -1);
        }
        if (movingRight)
        {
            move_left_and_right(deltaTime, 1);
        }
    }

    Player(const string &texture_path, float width, float height)
    {
        if (!texture.loadFromFile(texture_path)) {
            cerr << "Failed to load texture from " << texture_path << endl;
            return;
        };
        player.setTexture(texture);
        player.setTextureRect(sf::IntRect(
            static_cast<int>(WIN_X / 2.f), static_cast<int>(WIN_Y / 2.f), 
            width, height
        ));
        sf::FloatRect spriteBounds = player.getGlobalBounds();
        player.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
        player.setPosition(WIN_X / 2.f, WIN_Y / 2.f);
    };  

    void move_left_and_right(float deltaTime, float direction)
    {
        float movement = calculate_smooth_movement(deltaTime, direction, speed);
        player.move(movement, 0.f);
        is_behind_map();
    };

    void move_forward(float deltaTime, float direction)
    {
        float movement = calculate_smooth_movement(deltaTime, direction, speed);
        player.move(0.f, movement);
        is_behind_map();
    };

    void rotate(float deltaTime, float direction)
    {
        float movement = calculate_smooth_movement(deltaTime, direction, speed);
        player.rotate(movement);
    };
};
