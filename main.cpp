#include <iostream>
#include <cmath>
using namespace std;

#include <SFML/Graphics.hpp>

class Particle
{
public:
    sf::CircleShape circle;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float radius;

    Particle(double r, sf::Vector2f pos, sf::Vector2f vel, float mass):radius(r), position(pos), velocity(vel), mass(mass){
        circle.setRadius(radius);
        circle.setOrigin(sf::Vector2f(radius, radius));
        acceleration = sf::Vector2f(0, 0);
    }

    void update(float &dt){

        velocity.x = acceleration.x * dt;
        velocity.y = acceleration.y * dt;

        position.x += velocity.x * dt * 60;
        position.y += velocity.y * dt * 60;
        circle.setPosition(position);
    }

    void render(sf::RenderWindow &win){
        win.draw(circle);
    }
};

float distance(sf::Vector2f &a, sf::Vector2f &b){
    return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

sf::Vector2f force(Particle &a, Particle &b){
    double gravity_constant = 6.67428e-11;

    sf::Vector2f u = (b.position - a.position) / distance(a.position, b.position);

    float dist = distance(a.position, b.position);

    double scale_factor = (gravity_constant * a.mass * b.mass) / (1.6434e17);
    sf::Vector2f Force(scale_factor * u.x, scale_factor * u.y);

    float ax = Force.x / (a.mass * b.mass);
    float ay = Force.y / (a.mass * b.mass);

    return sf::Vector2f(ax, ay); // acceleration
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Moon Simulation");

    sf::Clock clock;
    float dt;  

    Particle moon(20.0, sf::Vector2f(400, 360), sf::Vector2f(1, 1), 7.35e22);
    Particle planet(40.0, sf::Vector2f(620, 360), sf::Vector2f(0, 0), 5.97e24);

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

        sf::Vector2f acceleration = force(planet, moon);

        cout << acceleration.x << " " << acceleration.y << endl;

        moon.acceleration = acceleration;

        window.clear();

        moon.update(dt);
        moon.render(window);
        planet.update(dt);
        planet.render(window);
        window.display();

    }

    return 0;
}