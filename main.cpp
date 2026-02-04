#include "raylib.h"
#include <cmath>

class Planet {
public:
    Vector2 pos;
    Vector2 vel;
    float mass;
    float radius;
    Color color;

    Planet(Vector2 p, Vector2 v, float m, float r, Color c) {
        pos = p;
        vel = v;
        mass = m;
        radius = r;
        color = c;
    }

    void ApplyGravity(const Planet& other, float G) {
        Vector2 dir = {
            other.pos.x - pos.x,
            other.pos.y - pos.y
        };

        float distSq = dir.x * dir.x + dir.y * dir.y + 25.0f;
        float dist = sqrtf(distSq);

        Vector2 norm = {
            dir.x / dist,
            dir.y / dist
        };

        float force = G * mass * other.mass / distSq;

        Vector2 accel = {
            norm.x * (force / mass),
            norm.y * (force / mass)
        };

        vel.x += accel.x;
        vel.y += accel.y;
    }

    void Update(float dt) {
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }

    void Draw() const {
        DrawCircleV(pos, radius, color);
    }
};

int zoomfactor = 1;

int main() {
    InitWindow(1000, 700, "Planet Gravity Simulation");
    SetTargetFPS(60);

    const float G = 300.0f;

    Planet sun(
        {500, 350},
        {0, 0},
        50,
        25,
        ORANGE
    );

    Planet earth(
        {500, 150},
        {40, 0},
        100,
        6,
        SKYBLUE
    );

    Planet planet2(
        {500, 300},
        {100, 0},
        20,
        3,
        RED
    );

    Camera2D camera = {0};
    camera.target = {500, 350};
    camera.offset = {500, 350};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    static bool panning = false;
    static Vector2 lastMouse = {0};

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        earth.ApplyGravity(sun, G);
        planet2.ApplyGravity(earth, G);
        planet2.Update(dt);
        earth.Update(dt);
        
        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);

        sun.Draw();
        earth.Draw();
        planet2.Draw();


        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            Vector2 mouseWorldPos =
                GetScreenToWorld2D(GetMousePosition(), camera);

            camera.target = mouseWorldPos;

            camera.zoom += wheel * 0.1f;
            if (camera.zoom < 0.1f) camera.zoom = 0.1f;
            if (camera.zoom > 10.0f) camera.zoom = 10.0f;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            panning = true;
            lastMouse = GetMousePosition();
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            panning = false;
        }

        if (panning) {
            Vector2 mouse = GetMousePosition();
            Vector2 delta = {
                mouse.x - lastMouse.x,
                mouse.y - lastMouse.y
            };

            camera.target.x -= delta.x / camera.zoom;
            camera.target.y -= delta.y / camera.zoom;

            lastMouse = mouse;
        }

        if (IsKeyPressed(KEY_C)) {
            camera.target = sun.pos;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
