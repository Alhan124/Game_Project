#include "raylib.h"
#include <stdio.h>

typedef struct player{
    Vector2 position;
    Vector2 size;
    bool jump;
    int speed;
    int jump_height;
} Player;

static Player player = {0};
int main(){
    const int screenWidth = 800;
    const int screenHeight = 600;
    int gravity = 9.8;
    player.position = (Vector2){ screenHeight/2,screenWidth/2+100 };
    player.size = (Vector2){50,50};
    player.speed = 10;
    player.jump = true;
    player.jump_height = 20;
    
    
    InitWindow(screenWidth, screenHeight, "raylib ");
    SetTargetFPS(60);      


    while (!WindowShouldClose()){
        ClearBackground(BLACK);
        BeginDrawing();
        DrawRectangle(player.position.x,player.position.y,player.size.x,player.size.y,RED);
         
        EndDrawing();
        
        player.position.y += gravity;
        if (player.position.y >= 540){
            
            gravity = 0;
        }else{
            gravity = 9.8;
        }
        if (IsKeyDown(KEY_SPACE) && player.jump == true){
            player.position.y -= player.jump_height;
        }
        if (IsKeyDown('A')){
            player.position.x -= player.speed;
        }
        if (IsKeyDown('D')){
            player.position.x += player.speed;   
        }        
    }
    
    
    return 0;
    
    
    
}

