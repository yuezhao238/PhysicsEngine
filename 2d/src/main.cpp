#include <iostream>
#include <SFML/Graphics.hpp>
#include "physics_engine.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Physics Engine");

    PhysicsEngine engine;

    RigidBody body1({100, 100}, 1);
    RigidBody body2({200, 100}, 1);

    engine.addRigidBody(&body1);
    engine.addRigidBody(&body2);

    body1.applyForce({10000, 0});
    body2.applyForce({-10000, 0});

    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        engine.update(dt);

        window.clear();
        engine.render(window);
        window.display();
    }
}