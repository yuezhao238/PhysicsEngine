#include <iostream>
#include <SFML/Graphics.hpp>
#include "physics_engine.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Physics Engine");

    PhysicsEngine engine;

    RigidBody body1({200, 200}, 999999999, {0, 0});
    RigidBody body2({300, 200}, 0.00001, {0, 1});

    engine.addRigidBody(&body1);
    engine.addRigidBody(&body2);

    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // float dt = clock.restart().asSeconds();
        float dt = 0.1;
        
        // sf::sleep(sf::seconds(0.2));

        engine.update(dt);
        std::cout << "Body1: " << body1.position.x << ", " << body1.position.y << std::endl;
        std::cout << "Body2: " << body2.position.x << ", " << body2.position.y << std::endl;

        window.clear();
        engine.render(window);
        window.display();
    }
}