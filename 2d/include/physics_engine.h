#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

struct Vector2 {
    float x, y;
    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vector2 operator/(float scalar) const {
        return {x / scalar, y / scalar};
    }

    float lengthSquare() const {
        return std::sqrt(x * x + y * y);
    }
};

struct AABB {
    Vector2 min;
    Vector2 max;

    bool overlaps(const AABB& other) const {
        return !(max.x < other.min.x || min.x > other.max.x || max.y < other.min.y || min.y > other.max.y);
    }
};

class RigidBody {
public:
    Vector2 position;
    Vector2 velocity;
    Vector2 force;
    float mass;
    sf::CircleShape shape;

    RigidBody(Vector2 pos, float m, Vector2 vel) : position(pos), mass(m), velocity(vel), force({0, 0}) {
        shape.setRadius(10);
        shape.setOrigin(10, 10);
        shape.setPosition(pos.x, pos.y);
        shape.setFillColor(sf::Color::Green);
    }

    void applyForce(const Vector2& f) {
        force = force + f;
    }

    void integrate(float dt) {
        Vector2 acceleration = force / mass;
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt;
        shape.setPosition(position.x, position.y);
        force = {0, 0};
    }

    AABB getAABB() const {
        float radius = shape.getRadius();
        return {{position.x - radius, position.y - radius}, {position.x + radius, position.y + radius}};
    }

    void resolveCollision(RigidBody& other) {
        velocity = velocity * -1;
        other.velocity = other.velocity * -1;
    }
};

class PhysicsEngine {
public:
    std::vector<RigidBody*> bodies;
    Vector2 universalGravity(RigidBody* body1, RigidBody* body2);
    Vector2 allUniversalGravity(RigidBody* body);

    void addRigidBody(RigidBody* body) {
        bodies.push_back(body);
    }

    void update(float dt) {
        

        for (RigidBody* body : bodies) {
            body->applyForce(allUniversalGravity(body));
            body->integrate(dt);
        }

        for (size_t i = 0; i < bodies.size(); ++i) {
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                if (bodies[i]->getAABB().overlaps(bodies[j]->getAABB())) {
                    bodies[i]->resolveCollision(*bodies[j]);
                }
            }
        }
    }

    void render(sf::RenderWindow& window) {
        for (RigidBody* body : bodies) {
            window.draw(body->shape);
        }
    }



};

#endif // PHYSICS_ENGINE_H
