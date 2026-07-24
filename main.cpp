#include "gameObject.hpp"
#include "raylib.h"
#include "raymath.h"

using namespace std;

void ui(){
		
	DrawRectangleV({100,100},{600,200},GREEN);
}

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 400;

	InitWindow(screenWidth, screenHeight, "main!");
	SetTargetFPS(90);

	gameObject player;
	player.playerPos = {400,200};
	player.playerSize = {30,30};
	player.playerColor = BLUE;

	Vector2 blockPos[] ={{0,0},{0,390},{0,0},{790,0}};
	Vector2 blockSize[] = {{10,400},{800,10},{800,10},{10,400}};
	
	float timer = 5;
	Vector2 enemyPos = {550,350};
	Vector2 enemySize = {30,30};
	Color enemyCol = PINK;

	float spd = 100.0f;
	
	Vector2 bookShelfPos = {30,12};
	Vector2 bookShelfSize = {30,50};
	Color bookShelfCol = DARKGRAY;

	while(!WindowShouldClose()){
		//collsions!!!
		Rectangle collider1 = {player.playerPos.x, player.playerPos.y, player.playerSize.x, player.playerSize.y};
		const int n = sizeof(blockPos)/sizeof(blockPos[0]);

		for (int i = 0; i < n; i++){
			Rectangle collider = {blockPos[i].x, blockPos[i].y, blockSize[i].x, blockSize[i].y};
			if (CheckCollisionRecs(collider, collider1)){
				Rectangle overlap = GetCollisionRec(collider, collider1);

				if (overlap.width < overlap.height){
					if(player.playerPos.x < blockPos[i].x) player.playerPos.x -= overlap.width;
					else player.playerPos.x += overlap.width;
				}
				else{
					if(player.playerPos.y < blockPos[i].y) player.playerPos.y -= overlap.height;
					else player.playerPos.y += overlap.height;
				}
			}
		}


		player.movement(player.playerPos);
		
		if (timer > 0){
			timer -= GetFrameTime();
			if (timer < 0) timer = 0;
		}
		if (timer <= 0){
		Vector2 target = {player.playerPos.x, player.playerPos.y};
		enemyPos = Vector2MoveTowards(enemyPos, target, spd * GetFrameTime());
		}

		Rectangle bookShelf = {bookShelfPos.x, bookShelfPos.y, bookShelfSize.x, bookShelfSize.y};

		if (CheckCollisionRecs(collider1,bookShelf) && IsKeyDown(KEY_E)) ui();
		if (CheckCollisionRecs(collider1, bookShelf)) DrawText("press E to open",600,20,20,PURPLE);

		BeginDrawing();
		ClearBackground(BLACK);

		DrawRectangleV(bookShelfPos, bookShelfSize, bookShelfCol);

		player.draw(player.playerPos,player.playerSize,player.playerColor);
		
		const int count = sizeof(blockPos)/sizeof(blockPos[0]);

		for (int i = 0; i < count; i++){
			DrawRectangleV(blockPos[i], blockSize[i], GRAY);
		}
		
		DrawText(TextFormat("time: %i",(int)timer),10,10,20,YELLOW);
		if (timer <= 0){
			DrawRectangleV(enemyPos,enemySize,enemyCol);
		}

		EndDrawing();
	
	}
	CloseWindow();
	return 0;
}
