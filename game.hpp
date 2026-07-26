#include "raylib.h"
#include "raymath.h"
#include "cstring"
using namespace std;

struct character
{
	Vector2 spawn;
	Vector2 pos;
	Vector2 size;
	Color col;
	bool alive;
};

struct object
{
	Vector2 pos;
	Vector2 size;
};

struct puzzle
{
	Vector2 pos;
	Vector2 size;
	Color col;
};

struct textures
{
	Texture2D player;
	Texture2D desk;
	Texture2D computer;
	Texture2D table1;
	Texture2D table2;
	Texture2D shelf1;
	Texture2D shelf2;
	Texture2D Table1;
	Texture2D Table2;
	Texture2D Board;
	Texture2D Shelf1;
	Texture2D Shelf2;
	Texture2D DiaryPage;
	Texture2D folders;
	Texture2D folder1;
	Texture2D folder2;
	Texture2D folder3;
	Texture2D folder4;
	Texture2D paper;
	Texture2D order;
	Texture2D ending;
	Texture2D complete;
	Texture2D floor;
};

float mainTimer = 480;
float timer = mainTimer;
float speed = 100;

Vector2 deskPos = {330,100};
Vector2 deskSize = {170,60};

Vector2 computerPos = {335,110};
Vector2 computerSize = {35,35};

Vector2 boardPos = {12,50};
Vector2 boardSize = {5,300};

Vector2 table1Pos = {100,335};
Vector2 table1Size = {170,50};
Vector2 table2Pos = {450,335};
Vector2 table2Size = {200,50};

Vector2 shelf1Pos = {735,18};
Vector2 shelf1Size = {50,176};
Vector2 shelf2Pos = {735,208};
Vector2 shelf2Size = {50,176};

typedef enum GameScreen {MENU = 0,GAMEPLAY,COMPUTER,ORDERS,FOLDERS,FOLDER1,FOLDER2,FOLDER3,FOLDER4,BOARD,TABLE1,DIARY,TABLE2,SHELF1,SHELF2,COMPLETE,ENDING} GameScreen;

#define MAX_INPUT_CHARS  9
const char* Password = "x21aar";
char password[MAX_INPUT_CHARS] = "\0";
int letterCount = 0;

Rectangle textbox = {325,170,200,70};
bool mouseOnText = false;
int framesCounter = 0;

Rectangle playBtn = {320,170,150,50};

GameScreen currentScreen = MENU;
void gameUpdate(character& player, puzzle& puz, const object obj[], int count)
{
	if (timer > 0)
	{
		timer -= GetFrameTime();
		if (timer < 0) timer = 0;
	}

	switch(currentScreen)
	{
	case MENU:
	{
		if(CheckCollisionPointRec(GetMousePosition(),playBtn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = GAMEPLAY;
		else currentScreen = MENU;
	}break;
	case GAMEPLAY:
	{
		if(timer <= 0) currentScreen = ENDING;
		letterCount = 0;
		password[0] = '\0';
	if (IsKeyDown(KEY_W)) player.pos.y -= 2;
	if (IsKeyDown(KEY_S)) player.pos.y += 2;
	if (IsKeyDown(KEY_A)) player.pos.x -= 2;
	if (IsKeyDown(KEY_D)) player.pos.x += 2;

	Rectangle characterCollider = {player.pos.x,player.pos.y,player.size.x,player.size.y};

	for (int i = 0; i < count; i++)
	{
		Rectangle objectCollider = {obj[i].pos.x,obj[i].pos.y,obj[i].size.x,obj[i].size.y};
		if (CheckCollisionRecs(characterCollider,objectCollider))
		{
			Rectangle overlap = GetCollisionRec(characterCollider,objectCollider);

			if (overlap.width < overlap.height)
			{
				if (player.pos.x < obj[i].pos.x) player.pos.x -= overlap.width;
				else player.pos.x += overlap.width;
			}
			else
			{
				if (player.pos.y < obj[i].pos.y) player.pos.y -= overlap.height;
				else player.pos.y += overlap.height;
			}
		}
	}

	Rectangle puzzle = {puz.pos.x,puz.pos.y,puz.size.x,puz.size.y};
	Rectangle computer = {computerPos.x,computerPos.y,computerSize.x,computerSize.y};
	Rectangle board = {boardPos.x,boardPos.y,boardSize.x,boardSize.y};
	Rectangle table1 = {table1Pos.x,table1Pos.y,table1Size.x,table1Size.y};
	Rectangle table2 = {table2Pos.x,table2Pos.y,table2Size.x,table2Size.y};
	Rectangle shelf1 = {shelf1Pos.x,shelf1Pos.y,shelf1Size.x,shelf1Size.y};
	Rectangle shelf2 = {shelf2Pos.x,shelf2Pos.y,shelf2Size.x,shelf2Size.y};

	if (CheckCollisionPointRec(GetMousePosition(),puzzle)) DrawText("press E to inspect papers",300,12,20,PURPLE);
	if (CheckCollisionPointRec(GetMousePosition(),puzzle)&&IsMouseButtonDown(MOUSE_BUTTON_LEFT)) currentScreen = ORDERS;
	if (CheckCollisionPointRec(GetMousePosition(), computer))
	{
		DrawText("click to use computer",300,12,20,PURPLE);
	}
	if (CheckCollisionPointRec(GetMousePosition(),computer) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = COMPUTER;
	if (CheckCollisionPointRec(GetMousePosition(), board)) DrawText("click to inspect board",300,12,20,PURPLE);
	if (CheckCollisionPointRec(GetMousePosition(),table1)) DrawText("press E to inspect",300,12,20,PURPLE);
	if (CheckCollisionPointRec(GetMousePosition(),table2)) DrawText("press E to inspect",300,12,20,PURPLE);
	if (CheckCollisionPointRec(GetMousePosition(),shelf1)) DrawText("press E to inspect",300,12,20,PURPLE);
	if (CheckCollisionPointRec(GetMousePosition(),shelf2)) DrawText("press E to inspect",300,12,20,PURPLE);
	if (CheckCollisionPointRec(GetMousePosition(),board) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = BOARD;
	if (CheckCollisionPointRec(GetMousePosition(),table1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = TABLE1;
	if (CheckCollisionPointRec(GetMousePosition(),table2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = TABLE2;
	if (CheckCollisionPointRec(GetMousePosition(),shelf1) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = SHELF1;
	if (CheckCollisionPointRec(GetMousePosition(),shelf2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = SHELF2;
	}break;
	case COMPUTER:
	{
		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;
		if (timer <= 0) currentScreen = ENDING;

		if (CheckCollisionPointRec(GetMousePosition(),textbox)) mouseOnText = true;
		else mouseOnText = false;

		if(mouseOnText)
		{
			SetMouseCursor(MOUSE_CURSOR_IBEAM);
			int key = GetCharPressed();

			while (key > 0)
			{
				if((key>=32) && (key<=125) && (letterCount<MAX_INPUT_CHARS))
				{
					password[letterCount] = (char)key;
					password[letterCount+1] = '\0';
					letterCount++;
				}
				key = GetCharPressed();
			}
			if (IsKeyPressed(KEY_BACKSPACE))
			{
				letterCount--;
				if(letterCount < 0) letterCount = 0;
				password[letterCount] = '\0';
			}
			if(IsKeyPressed(KEY_ENTER))
			{
				if (strcmp(password, Password) == 0)
				{
					letterCount = 0;
					password[0] = '\0';
					currentScreen = FOLDERS;
				}
				else
				{
					letterCount = 0;
					password[0] = '\0';
				}
			}
		}
		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}break;
	case ORDERS:
	{
		if(timer <= 0) currentScreen = ENDING;
		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;
	}break;
	case FOLDERS:
	{
		if (timer <= 0) currentScreen = ENDING;
		Rectangle folder1 = {130,70,45,45};
		Rectangle folder2 = {180,150,45,45};
		Rectangle folder3 = {165,230,45,45};
		Rectangle folder4 = {235,250,45,45};


		if(CheckCollisionPointRec(GetMousePosition(), folder1)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = FOLDER1;
		if(CheckCollisionPointRec(GetMousePosition(), folder2)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = FOLDER2;
		if(CheckCollisionPointRec(GetMousePosition(), folder3)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = FOLDER3;
		if(CheckCollisionPointRec(GetMousePosition(), folder4)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = FOLDER4;
		if (IsKeyPressed(KEY_E)) currentScreen = COMPUTER;

	}break;
	case FOLDER1:
	{
		if (timer <= 0) currentScreen = ENDING;
		if (IsKeyPressed(KEY_E)) currentScreen = FOLDERS;
	}break;
	case FOLDER2:
	{	
		if (timer <= 0) currentScreen = ENDING;
		if (IsKeyPressed(KEY_E)) currentScreen = FOLDERS;

	}break;
	case FOLDER3:
	{
		if (timer <= 0) currentScreen = ENDING;
		if (IsKeyPressed(KEY_E)) currentScreen = FOLDERS;

	}break;
	case FOLDER4:
	{
		if (timer <= 0) currentScreen = ENDING;
		if (IsKeyPressed(KEY_E)) currentScreen = COMPLETE;
		timer = mainTimer;

	}break;
	case BOARD:
	{
		if (timer <= 0) currentScreen = ENDING;		
		Rectangle board = {boardPos.x,boardPos.y,boardSize.x,boardSize.y};
		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;
	}break;
	case TABLE1:
	{
		if (timer <= 0) currentScreen = ENDING;
		Rectangle diary = {440,90,190,250};
		Rectangle researchPaper = {100,90,180,250};

		if (CheckCollisionPointRec(GetMousePosition(),diary))
		{ 
			DrawText("Diary",500,12,20,PURPLE);
			if (CheckCollisionPointRec(GetMousePosition(),diary)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = DIARY;
		}
		if (CheckCollisionPointRec(GetMousePosition(),researchPaper)) DrawText("Research Papers",190,12,20,PURPLE);

		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;

	}break;
	case DIARY:
	{
		if (timer <= 0) currentScreen = ENDING;
		if (IsKeyDown(KEY_E)) currentScreen = TABLE1;

	}break;
	case TABLE2:
	{
		if (timer <= 0) currentScreen = ENDING;
		Rectangle table2 = {table2Pos.x,table2Pos.y,table2Size.x,table2Size.y};

		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;
	}break;
	case SHELF1:
	{
		if (timer <= 0) currentScreen = ENDING;
		Rectangle shelf1 = {shelf1Pos.x,shelf1Pos.y,shelf1Size.x,shelf1Size.y};

		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;
	}break;
	case SHELF2:
	{
		if (timer <= 0) currentScreen = ENDING;
		Rectangle shelf2 = {shelf2Pos.x,shelf2Pos.y,shelf2Size.x,shelf2Size.y};

		if(IsKeyPressed(KEY_E)) currentScreen = GAMEPLAY;
	}break;
	case COMPLETE:
	{
		Rectangle menu = {600,200,100,50};
		DrawRectangleRec(menu,DARKGREEN);
		if(CheckCollisionPointRec(GetMousePosition(),menu)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentScreen = MENU;
		else currentScreen = COMPLETE;
		DrawText("MENU",605,210,30,WHITE);
	}break;
	case ENDING:
	{
		if (IsKeyPressed(KEY_R)) currentScreen = GAMEPLAY;
	}break;
	default: break;
	}
}

void draw(textures& texture, character& player, puzzle& puz, const object obj[], int count)
{
	switch(currentScreen)
	{
	case MENU:
	{
		DrawRectangle(0,0,800,400,BLACK);
		DrawRectangleRec(playBtn,RED);
		DrawText("PLAY",340,175,40,DARKBLUE);
		
		if (CheckCollisionPointRec(GetMousePosition(),playBtn)) DrawRectangleLinesEx(playBtn,4,DARKGRAY);

		DrawText("8 MINUTES",190,80,70,YELLOW);
	}break;
	case GAMEPLAY:
	{
	DrawTextureEx(texture.floor,{0,0},0,1,WHITE);
	DrawText(TextFormat("timer: %i",(int)timer),10,10,20,YELLOW);
	DrawTextureEx(texture.paper,{90,70},0,1,WHITE);
	DrawTextureEx(texture.player,player.pos,0,1.6,WHITE);
	for (int i = 0; i < count; i++)
	{
		DrawRectangleV(obj[i].pos,obj[i].size,GRAY);
	}
	
	DrawTextureEx(texture.desk,{330,60},0,5,WHITE);
	DrawTextureEx(texture.computer,computerPos,0,1,WHITE);
	DrawRectangleV(boardPos,boardSize,DARKGREEN);
	DrawTextureEx(texture.table1,{100,255},0,5,WHITE);	
	DrawTextureEx(texture.table2,{400,255},0,5,WHITE);	
	DrawTextureEx(texture.shelf1,{670,-18},0,4,WHITE);	
	DrawTextureEx(texture.shelf2,{670,164},0,4,WHITE);


	}break;
	case COMPUTER:
	{
		DrawRectangle(100,100,600,200,GRAY);
		DrawRectangleRec(textbox,LIGHTGRAY);
		if(mouseOnText) DrawRectangleLines((int)textbox.x,(int)textbox.y,(int)textbox.width,(int)textbox.height,GREEN);
		else DrawRectangleLines((int)textbox.x,(int)textbox.y,(int)textbox.width,(int)textbox.height, DARKGRAY);

		DrawText(password, (int)textbox.x,(int)textbox.y+8, 30, DARKGRAY);
		DrawText(TextFormat("enter password %i/%i",letterCount,MAX_INPUT_CHARS),315,250,20,DARKGREEN);

		if(mouseOnText)
		{
			if(letterCount < MAX_INPUT_CHARS)
			{
				if(((framesCounter/20)%2)==0) DrawText("|",(int)textbox.x + MeasureText(password, 40),(int)textbox.y+12,40,MAROON);
			}
			else DrawText("backspace to delete",200,300,20,GRAY);
		}
	}break;
	case ORDERS:
	{
		DrawTextureEx(texture.order,{-230,10},0,2,WHITE);
	}break;
	case FOLDERS:
	{
		DrawTextureEx(texture.folders,{-190,0},0,1.9,WHITE);
	}break;
	case FOLDER1:
	{
		DrawTextureEx(texture.folder1,{0,0},0,1,WHITE);
	}break;
	case FOLDER2:
	{
		DrawTextureEx(texture.folder2,{0,0},0,1,WHITE);
	}break;
	case FOLDER3:
	{
		DrawTextureEx(texture.folder3,{0,0},0,1,WHITE);
	}break;
	case FOLDER4:
	{
		DrawTextureEx(texture.folder4,{0,0},0,1,WHITE);
	}break;
	case BOARD:
	{
		DrawTextureEx(texture.Board,{135,20},0,6,WHITE);

	}break;
	case TABLE1:
	{
		DrawTextureEx(texture.Table1,{100,20},0,6,WHITE);
	}break;
	case DIARY:
	{

		DrawTextureEx(texture.DiaryPage,{-200,5},0,2,WHITE);

	}break;
	case TABLE2:
	{
		DrawTextureEx(texture.Table2,{100,20},0,6,WHITE);
	}break;
	case SHELF1:
	{
		DrawTextureEx(texture.Shelf1,{80,2},0,7,WHITE);
	}break;
	case SHELF2:
	{
		DrawTextureEx(texture.Shelf2,{80,2},0,7,WHITE);
	}break;
	case ENDING:
	{
		DrawText("DEATH",310,12,50,RED);
		DrawText("press R to restart",300,64,20,RED);
		DrawTextureEx(texture.ending,{0,0},0,13,WHITE);
		player.pos = player.spawn;
		timer = mainTimer;

	}break;
	case COMPLETE:
	{
		DrawTextureEx(texture.complete,{0,0},0,1,WHITE);
	}break;
	default: break;
	}


}

void gameUnload(textures& texture)
{
	UnloadTexture(texture.desk);
}
