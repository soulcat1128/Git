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
		return x + animation.Width();
	}

	int CEraser::GetY2()
	{
		return y + animation.Height();
	}

	//static void setmap()
	//{
	//	for (int i = 0; i < 11; i++)
	//	{
	//		map_init[i][0] = 1;
	//	}
	//}
	void CEraser::Initialize()
	{
		//p = map_init;
		const int X_POS = 0;
		const int Y_POS = 0;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		/*
		animation.AddBitmap(IDB_ERASER1, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER3, RGB(255, 255, 255));
		animation.AddBitmap(IDB_ERASER2, RGB(255, 255, 255));
		*/
		animation.AddBitmap(Player1_down, RGB(255, 255, 255));
	}

	void CEraser::OnMove()
	{
		const int STEP_SIZE = 7;
		animation.OnMove();
		if (isMovingLeft &&  x > 0)
			x -= STEP_SIZE;
		if (isMovingRight && x < 980)
			x += STEP_SIZE;
		if (isMovingUp && y > 0)
			y -= STEP_SIZE;
		if (isMovingDown && y < 817)
			y += STEP_SIZE;
		//setmap();
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		//game_framework:: map_init[1][0] = 1;
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

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}