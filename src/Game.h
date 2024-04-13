#pragma once
#include "headers/Header.h"
#include "utils/ResourceManager.h"
#include "Scenes/Scene.h"
#include "Scenes/MainMenu.h"

class Game {
public:
    flecs::world world;
private:
    Scene* scene;
public:
    Game() = default;

    ~Game() = default;

    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    void init() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tetris");
        SetTargetFPS(FRAME_RATE);
        // WARNING: If you try to load textures before creating the window, you will face a segmentation fault
        // without any further explanation.
        RSC::loadTextures();

        world.import<RenderModule>();
        world.import<TransformModule>();
        // WARNING: import Modules first before creating any scene
        // because components needs to be registered first time inside the module
        // instead of the scenes

        scene = new MainMenu(world);

    }

    void run() {

        while (!WindowShouldClose()) {
            BeginDrawing();

                ClearBackground(RAYWHITE);

                Scene* newScene = scene->play();
                if (newScene != nullptr) {
                    auto oldScene = scene;
                    scene = newScene;
                    delete oldScene;
                }


            EndDrawing();
        }
    }
    static void exit() {
        CloseWindow();
    }


};

