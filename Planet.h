#ifndef PLANET_H
#define PLANET_H

#include "raylib.h"

class Planet {
public:
    Planet(Vector2 pos, Vector2 vel, float mass, float radius, Color color);

    void ApplyGravity(Planet& other);
    void Update();
    void Draw() const;

    Vector2 position;
    Vector2 velocity;
    float mass;
    float radius;

private:
    Color color;
};

#endif
