#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int WINDOW_X = 800;
const int WINDOW_Y = 800;

const int randInt(const int min, const int max) {
    return min + (rand() % static_cast<int>(max - min + 1));
}


class ParticleSystem {
private:
    sf::VertexArray particles;
public:

    sf::VertexArray getParticles() {
        return particles;
    }

    void addParticle(int x, int y) {
        particles.append(sf::Vertex(sf::Vector2f(x, y)));
    }

    void fillParticles(int count) {
        for (int i = 0; i < count; i++) {
            const int x = randInt(0, WINDOW_X - 50);
            const int y = randInt(0, WINDOW_Y - 50);
            addParticle(x, y);
        }
    };

    void addGravityEffect() {
        for (int i = 0; i < particles.getVertexCount(); i++) {
            float calculatedY = particles[i].position.y + 9.8f;
            if (calculatedY > (static_cast<float>(WINDOW_Y)) - 20.f) {
                continue;
            }
            else {
                particles[i].position.y = calculatedY;
            }
        }
    }

    void addNoise(float noiseConstant) {
        float fnoiseConstant = noiseConstant;
        for (int i = 0; i < particles.getVertexCount(); i++) {
            particles[i].position.x = randInt(particles[i].position.x - fnoiseConstant, particles[i].position.x + fnoiseConstant);
            particles[i].position.y = randInt(particles[i].position.y - fnoiseConstant, particles[i].position.y + fnoiseConstant);
        }
    }

    void moveAllParticlesTo(int targetX, int targetY, float forceX, float forceY) {
        for (int i = 0; i < particles.getVertexCount(); i++) {
            float x = particles[i].position.x;
            float y = particles[i].position.y;
            if (x - targetX < 0) {
                particles[i].position.x = (particles[i].position.x + forceX);
            }
            if (x - targetX > 0) {
                particles[i].position.x = (particles[i].position.x - forceX);
            }
            if (y - targetY < 0) {
                particles[i].position.y = (particles[i].position.y + forceY);
            }
            if (y - targetY > 0) {
                particles[i].position.y = (particles[i].position.y - forceY);
            }
        }
    };
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Particle System");\
    srand(time(NULL));
    sf::Clock clock;

    ParticleSystem particleSystem;

    particleSystem.fillParticles(250);

    int lastCursorX = WINDOW_X / 2;
    int lastCursorY = WINDOW_Y / 2;

    float accumulatedTime = 0;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                lastCursorX = event.mouseMove.x;
                lastCursorY = event.mouseMove.y;
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                particleSystem.addParticle(event.mouseButton.x, event.mouseButton.y);
                particleSystem.fillParticles(50);
            }
        }

        window.clear();
        accumulatedTime += clock.restart().asSeconds();
        if (accumulatedTime >= 0.016f) { // 60 fps 
            //particleSystem.moveAllParticlesTo(lastCursorX, lastCursorY, 1.f, 1.f);
            accumulatedTime = 0.0f;
            particleSystem.addGravityEffect();
            particleSystem.addNoise(1.f);
        }
        window.draw(particleSystem.getParticles());
        window.display();
    }

    return 0;
}