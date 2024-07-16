#include "physics_engine.h"

Vector2 PhysicsEngine::universalGravity(RigidBody *body1, RigidBody *body2) {
    float G = 6.67430e-11;
    float m1 = body1->mass;
    float m2 = body2->mass;
    Vector2 r = body2->position - body1->position;
    Vector2 force = r * (G * m1 * m2 / r.lengthSquare());
    return force;
}

Vector2 PhysicsEngine::allUniversalGravity(RigidBody *body) {
    Vector2 force = {0, 0};
    for (RigidBody *other : bodies) {
        if (other != body) {
            force = force + universalGravity(body, other);
        }
    }
    return force;
}
