#include "raylib.h"
#include "raymath.h"
using namespace std;

class gameObject{
	public:
		Vector2 playerPos;
		Vector2 playerSize;
		Color playerColor;

		void draw(Vector2 playerPos, Vector2 playerSize, Color playerColor){
			DrawRectangleV(playerPos,playerSize,playerColor);
		}

		void movement(Vector2& playerPos){
			if (IsKeyDown(KEY_W)) playerPos.y -= 2.0f;
			if (IsKeyDown(KEY_S)) playerPos.y += 2.0f;
			if (IsKeyDown(KEY_A)) playerPos.x -= 2.0f;
			if (IsKeyDown(KEY_D)) playerPos.x += 2.0f;
		}

		void collider(Vector2& pos){
			
		}
};

class objects{
	public:
		Vector2 pos;
		Vector2 size;
		Color col;

		void draw(Vector2 pos, Vector2 size, Color col){
			DrawRectangleV(pos, size, col);
		}
};
