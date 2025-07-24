#include "raylib.h"

int main() {
    InitWindow(1280, 720, "Aetherbound");
    SetTargetFPS(120);
    
    Vector2 player = {100, 520};
    Vector2 velocity = {0, 0};
    float gravity = 600.0f;
    float jumpSpeed = -350.0f;
    bool onGround = false;
    
    Rectangle ground = {0, 620, 1280, 100};
    
    while (!WindowShouldClose()) {
        DrawFPS(10, 10);

        float dt = GetFrameTime();
        
        if (IsKeyDown(KEY_A)) velocity.x = -200;
        else if (IsKeyDown(KEY_D)) velocity.x = 200;
        else velocity.x = 0;
        
        if (IsKeyPressed(KEY_SPACE) && onGround) {
            velocity.y = jumpSpeed;
        }
        
        velocity.y += gravity * dt;
        player.x += velocity.x * dt;
        player.y += velocity.y * dt;
        
        Rectangle playerRect = {player.x, player.y, 32, 32};
        if (CheckCollisionRecs(playerRect, ground)) {
            player.y = ground.y - 32;
            velocity.y = 0;
            onGround = true;
        } else {
            onGround = false;
        }
        
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawRectangleRec(ground, DARKGREEN);
        DrawRectangleV(player, Vector2{32, 32}, RED);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}