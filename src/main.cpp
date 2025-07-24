#include "raylib.h"

#include <string>

typedef enum {
    ANIM_IDLE = 0,
    ANIM_RUN = 1,
    ANIM_HURT = 2,
    ANIM_ATTACK = 3
} AnimationState;

int main() {
    InitWindow(1280, 720, "Aetherbound");
    Font font = GetFontDefault();
    SetTargetFPS(120);
    
    Vector2 player = {100, 520};
    Vector2 velocity = {0, 0};
    float gravity = 600.0f;
    float jumpSpeed = -350.0f;
    bool onGround = false;
    
    Rectangle ground = {0, 620, 1280, 100};
    
    Texture2D animTextures[4];
    animTextures[ANIM_IDLE] = LoadTexture("resources/IDLE.png");
    animTextures[ANIM_RUN] = LoadTexture("resources/RUN.png");
    animTextures[ANIM_HURT] = LoadTexture("resources/HURT.png");
    animTextures[ANIM_ATTACK] = LoadTexture("resources/ATTACK.png");
    
    int frameCount[4] = {10, 16, 4, 7};
    
    AnimationState currentAnim = ANIM_IDLE;
    AnimationState previousAnim = ANIM_IDLE;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.1f; // anim speed
    
    bool isAttacking = false;
    bool isHurt = false;
    float attackTimer = 0.0f;
    float hurtTimer = 0.0f;
    float attackDuration = 0.7f;   // total atk time
    float hurtDuration = 0.4f;     // total hurt time
    
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        std::string fpsStr = std::to_string(GetFPS()) + " FPS";
        DrawText(fpsStr.c_str(), 10, 10, 20, BLACK);
        
        if (IsKeyDown(KEY_A)) velocity.x = -200;
        else if (IsKeyDown(KEY_D)) velocity.x = 200;
        else velocity.x = 0;
        
        if (IsKeyPressed(KEY_SPACE) && onGround) {
            velocity.y = jumpSpeed;
        }
        
        if (IsKeyPressed(KEY_X) && !isAttacking && !isHurt) {
            isAttacking = true;
            attackTimer = 0.0f;
        }
        
        if (IsKeyPressed(KEY_Z) && !isAttacking && !isHurt) {
            isHurt = true;
            hurtTimer = 0.0f;
        }
        
        // physics
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
        
        previousAnim = currentAnim;
        
        if (isAttacking) {
            currentAnim = ANIM_ATTACK;
            attackTimer += dt;
            if (attackTimer >= attackDuration) {
                isAttacking = false;
            }
        }
        else if (isHurt) {
            currentAnim = ANIM_HURT;
            hurtTimer += dt;
            if (hurtTimer >= hurtDuration) {
                isHurt = false;
            }
        }
        else if (velocity.x != 0) {
            currentAnim = ANIM_RUN;
        }
        else {
            currentAnim = ANIM_IDLE;
        }
        
        if (currentAnim != previousAnim) {
            currentFrame = 0;
            frameTimer = 0.0f;
        }
        
        frameTimer += dt;
        
        if (frameTimer >= frameTime) {
            frameTimer = 0.0f;
            currentFrame++;
            
            if (currentFrame >= frameCount[currentAnim]) {
                if (currentAnim == ANIM_ATTACK || currentAnim == ANIM_HURT) {
                    currentFrame = frameCount[currentAnim] - 1;
                } else {
                    currentFrame = 0;
                }
            }
        }
        
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawFPS(10, 10);
        
        DrawRectangleRec(ground, DARKGREEN);
        
        Texture2D currentTexture = animTextures[currentAnim];
        float frameWidth = (float)(currentTexture.width / frameCount[currentAnim]);
        float frameHeight = (float)(currentTexture.height);
        
        Rectangle sourceRec = {
            currentFrame * frameWidth,
            0,                                  
            frameWidth,                         
            frameHeight                         
        };
        
        Rectangle destRec = {
            player.x,
            player.y,
            frameWidth,
            frameHeight
        };
        
        DrawTexturePro(currentTexture, sourceRec, destRec, Vector2{0, 0}, 0.0f, WHITE);
        
        EndDrawing();
    }
    
    // cleanup
    for (int i = 0; i < 4; i++) {
        UnloadTexture(animTextures[i]);
    }
    
    CloseWindow();
    return 0;
}