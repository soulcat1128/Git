/*
 * mygame.cpp: 本檔案儲遊戲本身的class的implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)	
: CGameState(g)
{
}

void CBouncingBall::SetXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

void CBouncingBall::SetFloor(int floor)
{
	this->floor = floor;
}

void CBouncingBall::SetVelocity(int velocity)
{
	this->velocity = velocity;
	this->initial_velocity;
}

void CGameMap::RandomBouncingBall()
{
	//const int MAX_RAND_NUM = 10;
	//random_num = (rand() % MAX_RAND_NUM) + 1;
	//bballs = new CBouncingBall[random_num];
	//int ini_index = 0;
	//for(int row = 0; row < 4; row ++)
	//	for (int col = 0; col < 5; col++)
	//	{
	//		if (map[row][col] != 0 && ini_index < random_num)
	//		{
	//			InitializeBouncingBall(ini_index, row, col);
	//			ini_index++;
	//		}
	//	}
	//int X = (eraser.GetX1()/70);
	//int Y = (eraser.GetY1()/70);
}

void CGameMap::InitializeBouncingBall(int ini_index, int row, int col)
{
	const int VELOCITY = 10; /// 球的起始上升速度
	const int BALL_PIC_HEIGHT = 15; // 球圖片的高度
	int floor = Y + (row + 1) * MH-BALL_PIC_HEIGHT; // 設定球的落下點為Ma的下方
	bballs[ini_index].LoadBitmap();  // 戴入彈跳球的動畫
	bballs[ini_index].SetFloor(floor);  // 設定彈跳的起始水平面
	bballs[ini_index].SetVelocity(VELOCITY + col); // 設定彈跳的初始速度, 越右邊的彈得越高
	bballs[ini_index].SetXY(X+col * MW+MW/2, floor);  // 設定球的起始位置X座標為該Map一半的位置
}

void CGameMap::OnKeyDown(UINT nChar)
{
	const int KEY_SPACE = 0x20;
	//if (nChar == KEY_SPACE)
		//RandomBouncingBall();
		//map_init[1][1] = 9;
}
void CGameMap::OnMove()
{
	for (int i = 0; i < random_num; i++)
	{
		bballs[i].OnMove();
	}
}

CGameMap::~CGameMap()
{
}
void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(0);	// 一開始的loading進度為0%
	//
	// 開始載入資料
	//
	logo.LoadBitmap(LOGO);
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

CGameMap::CGameMap()
	:X(0), Y(0), MW(70), MH(70)
{
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 15; j++) {
			map[i][j] = map_init[i][j];
		}
	}
	random_num = 0;
}

void CGameMap::LoadBitmap()
{
	House_r.LoadBitmap(house_r,RGB(255,255,255));//1
	House_y.LoadBitmap(house_y, RGB(255, 255, 255));//2
	House_b.LoadBitmap(house_b, RGB(255, 255, 255));//3
	Blocks_r.LoadBitmap(blocks_r,RGB(255,255,255));//4
	Blocks_y.LoadBitmap(blocks_y, RGB(255, 255, 255));//5
	Wooden_box.LoadBitmap(wooden_box, RGB(255, 255, 255));//6
	Tree.LoadBitmap(tree, RGB(255, 255, 255));//7
	Grass.LoadBitmap(grass, RGB(255, 255, 255));//8

	Bomb.LoadBitmap(bomb, RGB(255, 255, 255));//水球test
}

void CGameMap::OnShow()
{
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 15; j++) {
			map[i][j] = map_init[i][j];
		}
	}
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 13; j++) {
			switch (map[j][i]) {
			case 0:
				break;
			case 1:
				House_r.SetTopLeft(X + (MW * i), Y + (MH * j));
				House_r.ShowBitmap();
				break;
			case 2:
				House_y.SetTopLeft(X + (MW * i), Y + (MH * j));
				House_y.ShowBitmap();
				break;
			case 3:
				House_b.SetTopLeft(X + (MW * i), Y + (MH * j));
				House_b.ShowBitmap();
				break;
			case 4:
				Blocks_r.SetTopLeft(X + (MW * i), Y + (MH * j));
				Blocks_r.ShowBitmap();
				break;
			case 5:
				Blocks_y.SetTopLeft(X + (MW * i), Y + (MH * j));
				Blocks_y.ShowBitmap();
				break;
			case 6:
				Wooden_box.SetTopLeft(X + (MW * i), Y + (MH * j));
				Wooden_box.ShowBitmap();
				break;
			case 7:
				Tree.SetTopLeft(X + (MW * i), Y + (MH * j));
				Tree.ShowBitmap();
				break;
			case 8:
				Grass.SetTopLeft(X + (MW * i), Y + (MH * j));
				Grass.ShowBitmap();
				break;
			case 9:
				Bomb.SetTopLeft(X + (MW * i), Y + (MH * j));
				Bomb.ShowBitmap();
				break;
			default:
				ASSERT(0);
			}
		}
	for (int i = 0; i < random_num; i++) {
		bballs[i].OnShow();
	}
}


CPractice::CPractice()
{
	x = y = 0;
}
void CPractice::OnMove()
{
	if (y <= SIZE_Y) {
		x += 3;
		y += 3;
	}
	else {
		x = y = 0;
	}
}

void CPractice::LoadBitmap()
{
	pic.LoadBitmap(IDB_BITMAP3);
}
void CPractice::OnShow()
{
	//pic.SetTopLeft(x, y);
	//pic.ShowBitmap();
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	const char KEY_SPACE = ' ';
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	//pDC->TextOut(120,220,"Please click mouse or press SPACE to begin.");
	//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
	if (ENABLE_GAME_PAUSE)
		//pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
	//pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}								

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//c_practice.LoadBitmap();
	//c_practice.LoadBitmap();
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	char str[80];								// Demo 數字對字串的轉換
	sprintf(str, "Game Over ! (%d)", counter / 30);
	pDC->TextOut(240,210,str);
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(0)
{
	picX = picY = 0;
	ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	delete [] ball;
}

void CGameStateRun::OnBeginState()
{
	const int BALL_GAP = 90;
	const int BALL_XY_OFFSET = 45;
	const int BALL_PER_ROW = 7;
	const int HITS_LEFT = 10;
	const int HITS_LEFT_X = 590;
	const int HITS_LEFT_Y = 0;
	const int BACKGROUND_X = 0;
	const int ANIMATION_SPEED = 15;
	for (int i = 0; i < NUMBALLS; i++) {				// 設定球的起始座標
		int x_pos = i % BALL_PER_ROW;
		int y_pos = i / BALL_PER_ROW;
		ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
		ball[i].SetDelay(x_pos);
		ball[i].SetIsAlive(true);
	}
	eraser.Initialize();
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	//CAudio::Instance()->Play(AUDIO_LAKE, true);			// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_DING, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_NTUT, true);			// 撥放 MIDI
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	//
	// 如果希望修改cursor的樣式，則將下面程式的commment取消即可
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	// 移動背景圖的座標
	//
	//practice.SetTopLeft(10, 10);
	c_practice.OnMove();
	if (picX <= SIZE_Y) {
		picX += 5;
		picY += 5;
	}
	else
	{
		picX = picY = 0;
	}
	practice.SetTopLeft(picX, picY);
	/*
	if (background.Top() > SIZE_Y)
		background.SetTopLeft(60 ,-background.Height());
	background.SetTopLeft(background.Left(),background.Top()+1);
	*/
	//
	// 移動球
	//
	int i;
	for (i=0; i < NUMBALLS; i++)
		ball[i].OnMove();
	//
	// 移動擦子
	//
	eraser.OnMove();
	//
	// 判斷擦子是否碰到球
	//
	for (i=0; i < NUMBALLS; i++)
		if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
			ball[i].SetIsAlive(false);
			CAudio::Instance()->Play(AUDIO_DING);
			hits_left.Add(-1);
			//
			// 若剩餘碰撞次數為0，則跳到Game Over狀態
			//
			if (hits_left.GetInteger() <= 0) {
				CAudio::Instance()->Stop(AUDIO_LAKE);	// 停止 WAVE
				CAudio::Instance()->Stop(AUDIO_NTUT);	// 停止 MIDI
				GotoGameState(GAME_STATE_OVER);
			}
		}
	//
	// 移動彈跳的球
	//
	bball.OnMove();
	gamemap.OnMove();
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	c_practice.LoadBitmap();
	gamemap.LoadBitmap();
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	int i;
	for (i = 0; i < NUMBALLS; i++)	
		ball[i].LoadBitmap();								// 載入第i個球的圖形
	eraser.LoadBitmap();
	background.LoadBitmap(backgroundTest1);					// 載入背景的圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	//Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 繼續載入其他資料
	//
	//practice.LoadBitmap(IDB_BITMAP3, RGB(255, 255, 255));
	practice.LoadBitmap(IDB_BITMAP3);
	help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// 載入說明的圖形
	corner.LoadBitmap(IDB_CORNER);							// 載入角落圖形
	corner.ShowBitmap(background);							// 將corner貼到background
	bball.LoadBitmap();										// 載入圖形
	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// 載入編號0的聲音ding.wav
	//CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// 載入編號1的聲音lake.mp3
	CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\music.mp3");	// 載入編號2的聲音ntut.mid
	//
	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_SPACE = 0x20; // keyboard下箭頭
	gamemap.OnKeyDown(nChar);
	int GetX = eraser.GetX1()/ 70;
	int GetY = eraser.GetY1()/ 70;
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	//if (nChar == KEY_RIGHT && (map_init[GetY][GetX+1] == 0 || map_init[GetY][GetX+1] == 9))
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);
	if (nChar == KEY_SPACE)
		map_init[(eraser.GetY1()+35)/70][(eraser.GetX1()+35)/70] = 9;
		eraser.SetMap(map_init);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	eraser.SetMovingLeft(true);
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	eraser.SetMovingLeft(false);
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	// 沒事。如果需要處理滑鼠移動的話，寫code在這裡
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	eraser.SetMovingRight(true);
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	eraser.SetMovingRight(false);
}

void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//  貼上背景圖、撞擊數、球、擦子、彈跳的球
	//
	background.ShowBitmap();			// 貼上背景圖
	help.ShowBitmap();					// 貼上說明圖
	hits_left.ShowBitmap();				// 貼上彈跳的球
	
	//
	//  貼上左上及右下角落的圖
	//
	gamemap.OnShow();
	corner.SetTopLeft(0,0);
	corner.ShowBitmap();
	corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
	corner.ShowBitmap();
	eraser.OnShow();					// 貼上擦子
	//practice.ShowBitmap();
	//c_practice.OnShow();
	for (int i = 0; i < NUMBALLS; i++)
		ball[i].OnShow();				// 貼上第i號球
	bball.OnShow();

}
}