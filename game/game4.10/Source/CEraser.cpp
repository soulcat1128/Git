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
		//return x + animation.Width();
		return x + 70;
	}

	int CEraser::GetY2()
	{
		//return y + animation.Height();
		return y + 93;
	}

	void CEraser::Initialize()
	{
		const int X_POS = 0;
		const int Y_POS = 0;
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
		const int STEP_SIZE = 10;
		int GetX = x / 70;
		int GetY = y / 70;
		//animation.OnMove();
		if (isMovingUp && y > 0 && (map_init[GetY - 1][GetX] == 0 || map_init[GetY - 1][GetX] == 9)) {
			y -= STEP_SIZE;
			mode = 0;
		}
		else if (isMovingDown && y < 817 && (map_init[GetY + 1][GetX] == 0 || map_init[GetY + 1][GetX] == 9)) {
			y += STEP_SIZE;
			mode = 1;
		}

		else if (isMovingLeft && x > 0 && (map_init[GetY][GetX - 1] == 0 || map_init[GetY][GetX - 1] == 9)) {
			x -= STEP_SIZE;
			mode = 2;
		}
		else if (isMovingRight && x < 980 && (map_init[GetY][GetX + 1] == 0 || map_init[GetY][GetX + 1] == 9)){
		//else if (isMovingRight && x < 980) {
			x += STEP_SIZE;
			mode = 3;
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
				map_init[i][j] = map[i][j];
			}
		}
	}
	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
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