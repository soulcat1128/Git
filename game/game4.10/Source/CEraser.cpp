#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + 70;
	}

	int CEraser::GetY2()
	{
		return y + 93;
	}

	void CEraser::Initialize()
	{
		const int X_POS = 0;
		const int Y_POS = 0;
		isAlive = true;
		explosionRange = 1;
		speed = 10;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		mode = 0;
	}

	void CEraser::LoadBitmap()
	{
		/*
		animation.AddBitmap(IDB_ERASER1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		*/
		P1_down.LoadBitmap(Player1_down, RGB(255, 255, 255));
		P1_up.LoadBitmap(Player1_up, RGB(255, 255, 255));
		P1_left.LoadBitmap(Player1_left, RGB(255, 255, 255));
		P1_right.LoadBitmap(Player1_right, RGB(255, 255, 255));
	}

	void CEraser::OnMove()
	{
		
		//const int speed = 10;
		int x2 = GetX2();
		int y2 = GetY2();

		if (isMovingUp) {
			if (y > 0 && (map_user[(y - speed) / 70][(x + 35) / 70] == 0 || map_user[(y - speed) / 70][(x + 35) / 70] >= 9)) {
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
			if (y < 817 && (map_user[(y2 + speed) / 70][(x + 35) / 70] == 0 || map_user[(y2 + speed)/70][(x + 35) / 70] >= 9)) {
				y += speed;
				mode = 1;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (y  < 817 && (map_user[(y2 + temp) / 70][(x + 35) / 70] == 0 || map_user[(y2 + temp)/70][(x + 35) / 70] == 9))
					{
						y++;
					}
				}
			}
		}
		else if (isMovingLeft) {
			if (x > 0 && (map_user[(y + 49) / 70][(x - speed) / 70] == 0 || map_user[(y + 49) / 70][(x - speed) / 70] >= 9)) {
				x -= speed;
				mode = 2;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (x > 0 && (map_user[(y + 49) / 70][(x - temp) / 70] == 0 || map_user[(y + 49) / 70][(x - temp) / 70] == 9))
					{
						x--;
					}
				}

			}
		}
		else if (isMovingRight) {
			if (x < 980 && (map_user[(y + 49) / 70][(x2 + speed) / 70] == 0 || map_user[(y + 49) / 70][(x2 + speed) / 70] >= 9)) {
				x += speed;
				mode = 3;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (x < 980 && (map_user[(y + 49) / 70][(x2 + temp) / 70] == 0 || map_user[(y + 49) / 70][(x2 + temp) / 70] == 9))
					{
						x++;
					}
				}
			}
		}

		

	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;

	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetMap(int map[13][15])
	{
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				map_user[i][j] = map[i][j];
			}
		}
	}
	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void CEraser::SetSpeed(int inSpeed)
	{
		speed = inSpeed;
	}
	void CEraser::OnShow()
	{
		if (mode == 0) {
			P1_up.SetTopLeft(x, y);
			P1_up.ShowBitmap();
		}
		if (mode == 1) {
			P1_down.SetTopLeft(x, y);
			P1_down.ShowBitmap();
		}
		if (mode == 2) {
			P1_left.SetTopLeft(x, y);
			P1_left.ShowBitmap();
		}
		if (mode == 3) {
			P1_right.SetTopLeft(x, y);
			P1_right.ShowBitmap();
		}
	}
}