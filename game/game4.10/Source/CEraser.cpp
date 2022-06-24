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
		Initialize(0);
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
	void CEraser::setid(int id)
	{
		user_id = id;
	}
	void CEraser::Initialize(int who)
	{
		setid(who);

		int X_POS = 0;
		int Y_POS = 0;
		if (user_id == 2)
		{
			X_POS = 967;
			Y_POS = 817;
		}

		isAlive = true;
		explosionRange = 1;
		speed = 10;
		status = 5;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		mode = 0;
	}
	void CEraser::setP1Status(int s)
	{
		if (user_id == 1)
		{
			status = s;
		}
	}
	void CEraser::setP2Status(int s)
	{
		if(user_id == 2)
			status = s;
	}

	void CEraser::LoadBitmap()
	{
		P1_down.LoadBitmap(Player1_down, RGB(255, 255, 255));
		P1_up.LoadBitmap(Player1_up, RGB(255, 255, 255));
		P1_left.LoadBitmap(Player1_left, RGB(255, 255, 255));
		P1_right.LoadBitmap(Player1_right, RGB(255, 255, 255));
		p1die1.LoadBitmap(".\\res\\Player1_die1.bmp", RGB(255, 255, 255));
		p1die2.LoadBitmap(".\\res\\Player1_die2.bmp", RGB(255, 255, 255));

		P2_down.LoadBitmap(Player2_down, RGB(255, 255, 255));
		P2_up.LoadBitmap(Player2_up, RGB(255, 255, 255));
		P2_left.LoadBitmap(Player2_left, RGB(255, 255, 255));
		P2_right.LoadBitmap(Player2_right, RGB(255, 255, 255));
		p2die1.LoadBitmap(".\\res\\Player2_die1.bmp", RGB(255, 255, 255));
		p2die2.LoadBitmap(".\\res\\Player2_die2.bmp", RGB(255, 255, 255));
	}

	void CEraser::OnMove()
	{

		int x2 = GetX2();
		int y2 = GetY2();

		if (isMovingUp) {
			if (y > 0 && (map_user[(y - speed) / 70][(x + 35) / 70] == 0 || map_user[(y - speed) / 70][(x + 35) / 70] > 20)) {
				y -= speed;
				mode = 0;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (y > 0 && (map_user[(y - temp) / 70][(x + 35) / 70] == 0 || map_user[(y - temp) / 70][(x + 35) / 70] > 20))
					{
							y--;
					}
				}
			}
		}
		else if (isMovingDown) {
			if (y < 817 && (map_user[(y2 + speed) / 70][(x + 35) / 70] == 0 || map_user[(y2 + speed)/70][(x + 35) / 70] > 20)) {
				y += speed;
				mode = 1;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (y  < 817 && (map_user[(y2 + temp) / 70][(x + 35) / 70] == 0 || map_user[(y2 + temp)/70][(x + 35) / 70] > 20))
					{
						y++;
					}
				}
			}
		}
		else if (isMovingLeft) {
			if (x > 0 && (map_user[(y + 35) / 70][(x - speed) / 70] == 0 || map_user[(y + 35) / 70][(x - speed) / 70] > 20)) {
				x -= speed;
				mode = 2;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (x > 0 && (map_user[(y + 35) / 70][(x - temp) / 70] == 0 || map_user[(y + 35) / 70][(x - temp) / 70] > 20))
					{
						x--;
					}
				}
			}
		}
		else if (isMovingRight) {
			if (x < 980 && (map_user[(y + 35) / 70][(x2 + speed) / 70] == 0 || map_user[(y + 35) / 70][(x2 + speed) / 70] > 20)) {
				x += speed;
				mode = 3;
			}
			else
			{
				int temp = speed;
				while (temp > 0)
				{
					temp--;
					if (x < 980 && (map_user[(y + 35) / 70][(x2 + temp) / 70] == 0 || map_user[(y + 35) / 70][(x2 + temp) / 70] > 20))
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

	int CEraser::getStatus()
	{
		return status;
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
	int CEraser::getId()
	{
		return user_id;
	}
	void CEraser::SetSpeed(int inSpeed)
	{
		speed = inSpeed;
	}
	void CEraser::OnShow()
	{
		if (status == 5 && user_id == 1)
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
		else if(status != 5 && user_id == 1)
		{
			if (status == 4)
			{
				p1die1.SetTopLeft(x - 20, y - 8);
				p1die1.ShowBitmap();
			}
			else if (status == 3)
			{
				p1die2.SetTopLeft(x - 20, y - 8);
				p1die2.ShowBitmap();
			}
			else if (status == 2)
			{
				p1die1.SetTopLeft(x - 20, y - 8);
				p1die1.ShowBitmap();
			}
			else if (status == 1)
			{
				p1die2.SetTopLeft(x - 20, y - 8);
				p1die2.ShowBitmap();
			}


		}
		if (status == 5 && user_id == 2)
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
		else if (status != 5 && user_id == 2)
		{
			if (status == 4)
			{
				p2die1.SetTopLeft(x - 13, y - 8);
				p2die1.ShowBitmap();
			}
			else if (status == 3)
			{
				p2die2.SetTopLeft(x - 13, y - 8);
				p2die2.ShowBitmap();
			}
			else if (status == 2)
			{
				p2die1.SetTopLeft(x - 13, y - 8);
				p2die1.ShowBitmap();
			}
			else if (status == 1)
			{
				p2die2.SetTopLeft(x - 13, y - 8);
				p2die2.ShowBitmap();
			}


		}
	}
}