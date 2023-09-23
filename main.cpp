#include <iostream>
#include <cmath>
using namespace std;

#include <SFML/Graphics.hpp>

class Planet
{
public:
    sf::Vector2f position;
    float gravity_strengh;
    sf::CircleShape circle;

    Planet(sf::Vector2f pos, float gravity, int radius):position(pos), gravity_strengh(gravity){
        circle.setRadius(radius);
        circle.setOrigin(sf::Vector2f(radius, radius));
        circle.setFillColor(sf::Color(125, 190, 230));
        circle.setPosition(position);
    }

    void render(sf::RenderWindow &win){
        win.draw(circle);
    }

};


class Moon
{
public:
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;

    Moon(sf::Vector2f pos, sf::Vector2f vel, int radius):position(pos), velocity(vel){
        circle.setRadius(radius);
        circle.setOrigin(sf::Vector2f(radius, radius));
        circle.setFillColor(sf::Color(140, 140, 140));
        acceleration = sf::Vector2f(0, 0);
    }

    void update(Planet &planet, float &dt){
        
        // compute distance between planet and moon
        float dis_x = planet.position.x - position.x;
        float dis_y = planet.position.y - position.y;

        float direction = sqrt(dis_x * dis_x + dis_y * dis_y);

        float invert_direction = 1.f / direction;

        sf::Vector2f normalize_direction = sf::Vector2f(dis_x * invert_direction, dis_y * invert_direction);

        float inverse_square_dropoff = invert_direction * invert_direction;

        acceleration.x = normalize_direction.x * planet.gravity_strengh * inverse_square_dropoff;
        acceleration.y = normalize_direction.y * planet.gravity_strengh * inverse_square_dropoff;

        velocity.x += acceleration.x; // * dt;
        velocity.y += acceleration.y; // * dt;

        position.x += velocity.x; // * dt;
        position.y += velocity.y; // * dt;
        
    }

    void render(sf::RenderWindow &win){
        circle.setPosition(position);
        win.draw(circle);
    }
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Moon Simulation");
    window.setFramerateLimit(60);

    sf::Clock clock;
    float dt;

    Planet planet(sf::Vector2f(620, 360), 7000, 30);

    Moon moon(sf::Vector2f(620, 600), sf::Vector2f(5, 0), 10);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        dt = clock.restart().asSeconds();

        window.clear();

        moon.update(planet, dt);

        moon.render(window);
        
        planet.render(window);

        window.display();

    }

    return 0;
}