#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Play2.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Play2: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	Play2::Play2()
	{
		Initialize();
	}

	int Play2::GetX1()
	{
		return x;
	}

	int Play2::GetY1()
	{
		return y;
	}

	int Play2::GetX2()
	{
		return x + 83;
	}

	int Play2::GetY2()
	{
		return y + 93;
	}

	void Play2::Initialize()
	{
		const int X_POS = 967;
		const int Y_POS = 817;
		isAlive = true;
		explosionRange = 1;
		speed = 10;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		mode = 0;
	}

	void Play2::LoadBitmap()
	{
		P2_down.LoadBitmap(Player2_down, RGB(255, 255, 255));
		P2_up.LoadBitmap(Player2_up, RGB(255, 255, 255));
		P2_left.LoadBitmap(Player2_left, RGB(255, 255, 255));
		P2_right.LoadBitmap(Player2_right, RGB(255, 255, 255));
	}

	void Play2::OnMove()
	{
		int x2 = GetX2();
		int y2 = GetY2();

		if (isMovingUp) {
			if (y > 0 && (map_user[(y - speed) / 70][(x + 35) / 70] == 0 || map_user[(y - speed) / 70][(x + 35) / 70] == 9)) {
				y -= speed;
				mode = 0;
			}

			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (y > 0 && (map_user[(y - temp) / 70][(x + 35) / 70] == 0 || map_user[(y - temp) / 70][(x + 35) / 70] == 9))
					{
						y--;
					}
				}
			}
		}
		else if (isMovingDown) {
			if (y < 817 && (map_user[(y2 + speed) / 70][(x + 35) / 70] == 0 || map_user[(y2 + speed) / 70][(x + 35) / 70] == 9)) {
				y += speed;
				mode = 1;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (y < 817 && (map_user[(y2 + temp) / 70][(x + 35) / 70] == 0 || map_user[(y2 + temp) / 70][(x + 35) / 70] == 9))
					{
						y++;
					}
				}
			}
		}
		else if (isMovingLeft) {
			if (x > 0 && (map_user[(y + 69) / 70][(x - speed) / 70] == 0 || map_user[(y + 69) / 70][(x - speed) / 70] == 9)) {
				x -= speed;
				mode = 2;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (x > 0 && (map_user[(y + 69) / 70][(x - temp) / 70] == 0 || map_user[(y + 69) / 70][(x - temp) / 70] == 9))
					{
						x--;
					}
				}

			}
		}
		else if (isMovingRight) {
			if (x < 980 && (map_user[(y + 69) / 70][(x2 + speed) / 70] == 0 || map_user[(y + 69) / 70][(x2 + speed) / 70] == 9)) {
				x += speed;
				mode = 3;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (x < 980 && (map_user[(y + 69) / 70][(x2 + temp) / 70] == 0 || map_user[(y + 69) / 70][(x2 + temp) / 70] == 9))
					{
						x++;
					}
				}
			}
		}
	}

	void Play2::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Play2::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Play2::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Play2::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	void Play2::SetMap(int map[13][15])
	{
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				map_user[i][j] = map[i][j];
			}
		}
	}
	void Play2::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Play2::OnShow()
	{
		if (mode == 0) {
			P2_up.SetTopLeft(x, y);
			P2_up.ShowBitmap();
		}
		if (mode == 1) {
			P2_down.SetTopLeft(x, y);
			P2_down.ShowBitmap();
		}
		if (mode == 2) {
			P2_left.SetTopLeft(x, y);
			P2_left.ShowBitmap();
		}
		if (mode == 3) {
			P2_right.SetTopLeft(x, y);
			P2_right.ShowBitmap();
		}
	}
}