#include "raylib.h"
#include "raymath.h"
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

struct enemy
{
	Vector2 spawn;
	Vector2 pos;
	Vector2 size;
	Color col;
};

float timer = 10;
float speed = 100;

void gameUpdate(character& player, enemy& Enemy, const object obj[], int count)
{
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

	if (timer > 0)
	{
		timer -= GetFrameTime();
		if (timer < 0) timer = 0;
	}

	if (timer <= 0)
	{
		DrawRectangleV(Enemy.pos,Enemy.size,Enemy.col);
		Enemy.pos = Vector2MoveTowards(Enemy.pos, {player.pos.x,player.pos.y}, speed * GetFrameTime());
	}
	Rectangle enemy = {Enemy.pos.x,Enemy.pos.y,Enemy.size.x,Enemy.size.y};
	if (CheckCollisionRecs(characterCollider,enemy))
	{
		timer = 5;
		player.pos = player.spawn;
		Enemy.pos = Enemy.spawn;
	}

}

void draw(character& player, enemy& Enemy, const object obj[], int count)
{
	DrawText(TextFormat("timer: %i",(int)timer),10,10,20,YELLOW);
	DrawRectangleV(player.pos,player.size,player.col);
	for (int i = 0; i < count; i++)
	{
		DrawRectangleV(obj[i].pos,obj[i].size,GRAY);
	}
}
