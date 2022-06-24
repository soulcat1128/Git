﻿#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CBouncingBall.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CBouncingBall: BouncingBall class
	/////////////////////////////////////////////////////////////////////////////

	CBouncingBall::CBouncingBall()	// constructor
	{
		const int INITIAL_VELOCITY = 20;	// 初始上升速度
		const int FLOOR = 400;				// 地板座標
		floor = FLOOR;
		x = 910; y = 0;				// y座標比地板高1點(站在地板上)
		rising = true;						// true 上升 , false 下降
		initial_velocity = INITIAL_VELOCITY;// 初始速度
		velocity = initial_velocity;		// 目前速度
	}

	void CBouncingBall::LoadBitmap()
	{
		char *filename[3] = { ".\\res\\bomb.bmp",".\\res\\bomb2.bmp",".\\res\\explode.bmp"};
		for (int i = 0; i < 3; i++)	// 載入動畫(由4張圖形構成)
		{
			animation.AddBitmap(filename[i], RGB(255, 255, 255));
			animation.SetDelayCount(25);
		}
	}

	void CBouncingBall::OnMove()
	{

		//if (rising) {			// 上升狀態
		//	if (velocity > 0) {
		//		y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
		//		velocity--;		// 受重力影響，下次的上升速度降低
		//	}
		//	else {
		//		rising = false; // 當速度 <= 0，上升終止，下次改為下降
		//		velocity = 1;	// 下降的初速(velocity)為1
		//	}
		//}
		//else {				// 下降狀態
		//	if (y < floor - 1) {  // 當y座標還沒碰到地板
		//		y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
		//		velocity++;		// 受重力影響，下次的下降速度增加
		//	}
		//	else {
		//		y = floor - 1;  // 當y座標低於地板，更正為地板上
		//		rising = true;	// 探底反彈，下次改為上升
		//		velocity = initial_velocity; // 重設上升初始速度
		//	}
		//}
		animation.OnMove();		// 執行一次animation.OnMove()，animation才會換圖
	}

	void CBouncingBall::OnShow()
	{
		animation.SetTopLeft(x, y);
		animation.OnShow();
	}
}