#include <SFML/Graphics.hpp>

class Particle
{
private:
    sf::CircleShape circle;
    sf::Vector2f velocity;
    sf::Vector2f position;
    float radius;
public:
    Particle(double r, sf::Vector2f pos):radius(r), position(pos){
        circle.setRadius(radius);
        circle.setOrigin(sf::Vector2f(radius, radius));
    }

    void update(float &dt){
        position.x += velocity.x * dt * 60;
        position.y += velocity.y * dt * 60;
        circle.setPosition(position);
    }

    void render(sf::RenderWindow &win){
        win.draw(circle);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Moon Simulation");

    sf::Clock clock;
    float dt;

    Particle moon(20.0, sf::Vector2f(620, 360));

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        dt = clock.restart().asSeconds();

        window.clear();

        moon.update(dt);
        moon.render(window);
        window.display();

    }

    return 0;
}