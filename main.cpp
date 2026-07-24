#include "game.hpp"
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
	
	character player1;
	player1.spawn = {300,100};
	player1.pos = player1.spawn;
	player1.size = {30,30};
	player1.col = BLUE;

	enemy killer;
	killer.spawn = {100,100};
	killer.pos = killer.spawn;
	killer.size = {30,30};
	killer.col = DARKGRAY;

	object obj[4] = 
	{
		{{0,0},{10,400}},
		{{0,390},{800,10}},
		{{790,0},{10,400}},
		{{10,0},{800,10}}
	};

	int objCount = sizeof(obj)/sizeof(obj[0]);

	while(!WindowShouldClose()){
		
		gameUpdate(player1,killer,obj,objCount);

		BeginDrawing();
		ClearBackground(BLACK);
		
		draw(player1,killer,obj,objCount);
		
		EndDrawing();
	
	}
	CloseWindow();
	return 0;
}

