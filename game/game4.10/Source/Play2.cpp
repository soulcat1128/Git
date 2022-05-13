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
		return x + animation.Width();
	}

	int Play2::GetY2()
	{
		return y + animation.Height();
	}

	void Play2::Initialize()
	{
		const int X_POS = 980;
		const int Y_POS = 817;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void Play2::LoadBitmap()
	{
		/*
		animation.AddBitmap(IDB_ERASER1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		*/
		animation.AddBitmap(Player1_up, RGB(255, 255, 255));
	}

	void Play2::OnMove()
	{
		const int STEP_SIZE = 10;
		int GetX = x / 70;
		int GetY = y / 70;
		animation.OnMove();
		if (isMovingLeft &&  x > 0)
			x -= STEP_SIZE;
		//if (isMovingRight && x < 980 && (map_init[GetY][GetX + 1] == 0 || map_init[GetY][GetX + 1] == 9))
		if (isMovingRight && x < 980)
			x += STEP_SIZE;
		if (isMovingUp && y > 0)
			y -= STEP_SIZE;
		if (isMovingDown && y < 817)
			y += STEP_SIZE;
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
	//void Play2::SetMap(int map[13][15])
	//{
	//	for (int i = 0; i < 13; i++) {
	//		for (int j = 0; j < 15; j++) {
	//			map_init[i][j] = map[i][j];
	//		}
	//	}
	//}
	void Play2::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Play2::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}