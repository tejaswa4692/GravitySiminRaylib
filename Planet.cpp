#include "Planet.h"
#include <cmath>
#include <raylib.h>

static const float G = 200.0f;

Planet::Planet(Vector2 pos, Vector2 vel, float m, float r, Color c) {
    position = pos;
    velocity = vel;
    mass = m;
    radius = r;
    color = c;
}

void Planet::ApplyGravity(Planet& other) {
    Vector2 dir = {
        other.position.x - position.x,
        other.position.y - position.y
    };

    float distSq = dir.x * dir.x + dir.y * dir.y;
    float dist = sqrtf(distSq);

    if (dist < radius + other.radius || dist < 5.0f) return;

    Vector2 norm = { dir.x / dist, dir.y / dist };

    float force = G * (mass * other.mass) / distSq;
    Vector2 accel = { norm.x * (force / mass), norm.y * (force / mass) };

    velocity.x += accel.x * GetFrameTime();
    velocity.y += accel.y * GetFrameTime();
}

void Planet::Update() {
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();
}

void Planet::Draw() const {
    DrawCircleV(position, radius, color);
}
