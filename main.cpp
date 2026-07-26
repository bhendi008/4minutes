#include "game.hpp"
#include "raylib.h"
#include "raymath.h"
#include "filesystem"
#include "iostream"

using namespace std;

int main(void)
{
	const int screenWidth = 800;
	const int screenHeight = 400;

	InitWindow(screenWidth, screenHeight, "main!");
	SetTargetFPS(90);
	
	character player1;
	player1.spawn = {400,200};
	player1.pos = player1.spawn;
	player1.size = {45,45};
	player1.col = BLUE;

	puzzle order;
	order.pos = {90,70};
	order.size = {20,40};
	order.col = WHITE;

	object obj[] = 
	{
		{{0,0},{10,400}},
		{{0,390},{800,10}},
		{{790,0},{10,400}},
		{{10,0},{800,10}},
		{{334,100},{150,75}},
		{{12,50},{5,300}},
		{{100,300},{160,66}},
		{{480,300},{194,66}},
		{{682,18},{80,176}},
		{{682,208},{50,176}}
	};

	textures texture;
	texture.player = LoadTexture("assets/player.png");
	texture.desk = LoadTexture("assets/desk.png");
	texture.computer = LoadTexture("assets/computer.png");
	texture.table1 = LoadTexture("assets/table1.png");
	texture.table2 = LoadTexture("assets/table2.png");
	texture.shelf1 = LoadTexture("assets/shelf.png");
	texture.shelf2 = LoadTexture("assets/shelf_2.png");
	texture.Board = LoadTexture("assets/board.png");
	texture.Table1 = LoadTexture("assets/table_1.png");
	texture.Table2 = LoadTexture("assets/table_2.png");
	texture.Shelf1 = LoadTexture("assets/shelf1.png");
	texture.Shelf2 = LoadTexture("assets/shelf2.png");
	texture.DiaryPage = LoadTexture("assets/diaryPage.png");
	texture.folders = LoadTexture("assets/folders.png");
	texture.folder1 = LoadTexture("assets/folder1.png");
	texture.folder2 = LoadTexture("assets/folder2.png");
	texture.folder3 = LoadTexture("assets/folder3.png");
	texture.folder4 = LoadTexture("assets/folder4.png");
	texture.paper = LoadTexture("assets/paper.png");
	texture.order = LoadTexture("assets/order.png");
	texture.ending = LoadTexture("assets/ending.png");
	texture.complete = LoadTexture("assets/completion.png");
	texture.floor = LoadTexture("assets/floor3.png");

	GameScreen currentScreen = GAMEPLAY;

	int objCount = sizeof(obj)/sizeof(obj[0]);

	while(!WindowShouldClose()){
		
		gameUpdate(player1,order,obj,objCount);

		BeginDrawing();
		ClearBackground(BLACK);
		
		draw(texture,player1,order,obj,objCount);
		
		EndDrawing();
	
	}
	gameUnload(texture);
	CloseWindow();
	return 0;
}

