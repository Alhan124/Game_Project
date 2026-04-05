#include "raylib.h"
#include <stdio.h>

typedef struct player{
    Vector2 pos;
    Vector2 size;
    Vector2 speed;
    bool falling;   // to check for double jump validity
    bool on_ground; // for platform collision 
} Player;

static Player player = {0};

typedef struct platform{
    Rectangle rect;
} platform; 

typedef struct coin{
    Vector2 pos;
    float radius;
    bool collected;
}Coin;


char game_state = 's';
Coin coins[8] = {};
int coin_count = 0;
int coin_num = 0;
platform platforms[20] = {};
int count = 0;
const int screenWidth = 800;
const int screenHeight = 600;



    
    
void player_input(){
    if (IsKeyDown(KEY_SPACE) && player.on_ground){
            player.speed.y = -20;
            player.falling = true;
            player.on_ground = false;
        }
    
    if (IsKeyDown('A')){
        player.speed.x = -5;
    }
    else if (IsKeyDown('D')){
        player.speed.x = 5;   
    }else{
        player.speed.x = 0;
    }
    
    player.speed.y += 1.2;
    
    }
    



void set_platforms(){
    platforms[count].rect = (Rectangle){0,screenHeight-10,800,50};
    count++;
    platforms[count].rect = (Rectangle){100,500,100,20};
    count++;
    platforms[count].rect = (Rectangle){300,400,100,20};
    count++;
    platforms[count].rect = (Rectangle){500,300,100,20};
    count++;
    platforms[count].rect = (Rectangle){650,450,100,20};
    count++;
    platforms[count].rect = (Rectangle){10,350,60,20};
    count++;
}


void draw_plat(){
    for (int i = 0; i < count; i++){
        DrawRectangleRec(platforms[i].rect,WHITE);
    }
    
    
}


void set_coins(){
    coins[coin_count].pos = (Vector2){120,470};
    coins[coin_count].radius = 8;
    coins[coin_count].collected = false;
    coin_count++;
    
    coins[coin_count].pos = (Vector2){320,370};
    coins[coin_count].radius = 8;
    coins[coin_count].collected = false;
    coin_count++;
    
    coins[coin_count].pos = (Vector2){520,270};
    coins[coin_count].radius = 8;
    coins[coin_count].collected = false;
    coin_count++;
    
    coins[coin_count].pos = (Vector2){670,420};
    coins[coin_count].radius = 8;
    coins[coin_count].collected = false;
    coin_count++;
    
    coins[coin_count].pos = (Vector2){120,220};
    coins[coin_count].radius = 8;
    coins[coin_count].collected = false;
    coin_count++;
 }
    
    
    
    
void draw_coins(){
    for (int i = 0; i < coin_count; i++){
        if (!coins[i].collected){
            DrawCircleV(coins[i].pos,coins[i].radius,YELLOW);
        }
    }
}

    
void draw_game(){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangle(player.pos.x,player.pos.y,player.size.x,player.size.y,GRAY);
    draw_plat();
    draw_coins();
    EndDrawing();
}


void collision(){
    player.on_ground = false;
    
    
    player.pos.x += player.speed.x;
    Rectangle player_rect = {player.pos.x,player.pos.y,player.size.x,player.size.y};
    
    for (int i = 0; i < count; i++){
        if (CheckCollisionRecs(player_rect,platforms[i].rect)){
            if (player.speed.x > 0){
                player.pos.x = platforms[i].rect.x - player.size.x;
            }
            else if (player.speed.x < 0){
                player.pos.x = platforms[i].rect.x + platforms[i].rect.width;
            }
            
            player_rect = (Rectangle){player.pos.x,player.pos.y,player.size.x,player.size.y};  
        }
    }
    player.pos.y += player.speed.y;     
    player_rect = (Rectangle){player.pos.x,player.pos.y,player.size.x,player.size.y};  
        
    for (int i = 0; i < count; i++){
        if (CheckCollisionRecs(player_rect,platforms[i].rect)){
            if (player.speed.y > 0){
                        player.pos.y = platforms[i].rect.y - player.size.y;
                        player.speed.y = 0;
                        player.on_ground = true;
                    }
            else if (player.speed.y < 0){
                player.pos.y = platforms[i].rect.y + platforms[i].rect.height;
                player.speed.y = 0;
            }
            player_rect = (Rectangle){player.pos.x,player.pos.y,player.size.x,player.size.y};  
        }
    }
    
    for (int i = 0; i < coin_count; i++){
        if (!coins[i].collected){
            if (CheckCollisionCircleRec(coins[i].pos, coins[i].radius, (Rectangle){player.pos.x,player.pos.y,player.size.x,player.size.y})){
                coins[i].collected = true;
                coin_num++;
            }
        }
    }
    if (coin_num == coin_count){
        game_state = 'o';
    }
    
    if (player.pos.x+player.size.x <= 0){
        player.pos.x = screenWidth;
    }
    else if (player.pos.x >= screenWidth ){ 
        player.pos.x = screenWidth-player.pos.x;
        
    }
}



    

void menu(){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Platformer Game",screenWidth/2-200,50,40,WHITE);
    DrawText("by Alhan Suneer",screenWidth/2-200,100,20,WHITE);
    DrawText("Collect all the coins to win",screenWidth/2-150,180,20,WHITE);
    DrawText("Controls:",screenWidth/2-50,230,20,WHITE);
    DrawText("A/D - Move",screenWidth/2-150,280,20,WHITE);
    DrawText("Space - Jump",screenWidth/2-150,330,20,WHITE);
    DrawText("Shift - Dash",screenWidth/2-150,380,20,WHITE);
    DrawText("Press Enter to Begin...",screenWidth/2-200,450,30,WHITE);
    EndDrawing();
    if (IsKeyPressed(KEY_ENTER)){
        game_state = 'p';
    }
}


void over(){
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("YOU WIN",screenWidth/2-120,200,50,WHITE);
    DrawText("Press Enter to play again",screenWidth/2-160,300,30,WHITE);
    DrawText("Press Esc to Exit",screenWidth/2-140,350,30,WHITE);
    EndDrawing();
    
    if (IsKeyPressed(KEY_ESCAPE)){
        CloseWindow();
    }
    else if (IsKeyPressed(KEY_ENTER)){
        game_state = 's';
    }
}


int main(){
    
    player.pos = (Vector2){ screenHeight/2,screenWidth/2+100 };
    player.size = (Vector2){40,30};
    player.speed = (Vector2){0,0};
    player.on_ground = false;
    player.falling = true;
    set_platforms();
    set_coins();
    
    InitWindow(screenWidth, screenHeight, "raylib ");
    SetTargetFPS(60);      

    while (!WindowShouldClose()){
        switch (game_state){
            case 's':
                menu();
                break;
            case 'p':
                player_input();
                collision();
                draw_game();
                DrawText(TextFormat("Y: %.0f", player.pos.y), 10, 10, 20, WHITE);
                DrawText(TextFormat("X: %.0f", player.pos.x), 10, 40, 20, WHITE);
                break;
            case 'o':
                over();
                break;    
        }
        
    }
    
    
    return 0;
    
    
}
