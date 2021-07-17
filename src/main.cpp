#include "raylib.h"

#include <vector>
#include <iostream>
#include <memory>

#include "phys/particles/particle.h"
#include "phys/particles/particle_gravity.h"
#include "phys/particles/particle_drag.h"
#include "phys/particles/force_registry.h"

int main(void)
{
    // Raylib Init
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(screenWidth, screenHeight, "Vooronderzoek Lilyphys");

    // Camera
    Camera camera = { 0 };
    camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 75.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetTargetFPS(60);

    std::vector<std::shared_ptr<Particle>> particles;

    ForceRegistry registry;
    auto gravity = std::make_shared<ParticleGravity>(glm::vec3(0.0, -20.0f, 0.0));
    auto drag = std::make_shared<ParticleDrag>(5.0, 1.0);

    EnableCursor();

    // Game Loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateCamera(&camera);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        if (IsKeyPressed(KEY_SPACE))
        {
            auto particle = std::make_shared<Particle>();
            particle->set_mass(200.0f);
            registry.add(particle, gravity);
            registry.add(particle, drag);

            particles.push_back(particle);
        }

        registry.update_forces(1.0f / 60.0f);

        for (auto& particle : particles)
        {
            particle->integrate(1.0f / 60.0f);
            Vector3 pos{particle->get_position().x, particle->get_position().y, particle->get_position().z};
            DrawCube(pos, 1.0f, 1.0f, 1.0f, RED);
            DrawCubeWires(pos, 1.0f, 1.0f, 1.0f, RED);
        }

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("First person camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Move with keys: W, A, S, D", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse move to look around", 40, 60, 10, DARKGRAY);

        EndDrawing();
    }

    // Raylib deinit
    CloseWindow();

    return 0;
}