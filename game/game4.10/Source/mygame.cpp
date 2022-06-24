﻿#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "CGameMap.h"

namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)	
: CGameState(g)
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
	Operate.LoadBitmap(operate, RGB(255, 255, 255));
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 0x1B;
	const char KEY_SPACE = 0x20;
	const char KEY_ENTER = 0x0D;
	
	if (nChar == KEY_SPACE)
	{
		map_mode = 1;	//按Space進入地圖1
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	}
	else if (nChar == KEY_ENTER)
	{
		map_mode = 2;	//按Enter進入地圖2
		GotoGameState(GAME_STATE_RUN);						// 切換至GAME_STATE_RUN
	}
	else if (nChar == KEY_ESC)								// Demo 關閉遊戲的方法
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// 關閉遊戲
}



void CGameStateInit::OnShow()
{
	//
	// 貼上logo
	//
	logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
	logo.ShowBitmap();
	Operate.SetTopLeft(5,430);
	Operate.ShowBitmap();
	//
	// Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
	//
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f,*fp;
	f.CreatePointFont(160,"Times New Roman");	// 產生 font f; 160表示16 point的字
	fp=pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(0, 632,"Map selection:");
	pDC->TextOut(0, 656, "Press Space to the village");
	pDC->TextOut(0, 680, "Press Enter to the desert");
	pDC->TextOut(808,680,"Press Alt-F4 or ESC to Quit.");
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
	else if (counter == 120)
		CAudio::Instance()->Play(AUDIO_OVER, false);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
}

void CGameStateOver::OnInit()
{
	gameover.LoadBitmap(over, RGB(0, 0, 0));
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	//
	// 開始載入資料
	//
	//Sleep(300);				// 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
	//
	// 最終進度為100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	gameover.SetTopLeft((SIZE_X- gameover.Width())/2, (SIZE_Y- gameover.Height())/2);
	gameover.ShowBitmap();
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g), NUMBALLS(0)
{
	picX = picY = 0;
	//ball = new CBall [NUMBALLS];
}

CGameStateRun::~CGameStateRun()
{
	//delete [] ball;
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
	}
	eraser.Initialize(1);
	play2.Initialize(2);
	background.SetTopLeft(BACKGROUND_X,0);				// 設定背景的起始座標
	//help.SetTopLeft(0, SIZE_Y - help.Height());			// 設定說明圖的起始座標
	hits_left.SetInteger(HITS_LEFT);					// 指定剩下的撞擊數
	hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// 指定剩下撞擊數的座標
	CAudio::Instance()->Play(AUDIO_START, false);		// 撥放 WAVE
	CAudio::Instance()->Play(AUDIO_MUSIC, true);			// 撥放 MIDI
	if (map_mode == 1)
		gamemap.set_map(1);	//設定要載入的地圖
	else
		gamemap.set_map(2);	//設定要載入的地圖
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{

	if (picX <= SIZE_Y) {
		picX += 5;
		picY += 5;
	}
	else
	{
		picX = picY = 0;
	}
	practice.SetTopLeft(picX, picY);
	eraser.OnMove();
	play2.OnMove();
	gamemap.OnProps(eraser.GetX1(), eraser.GetY1(), 1);
	gamemap.OnProps(play2.GetX1(), play2.GetY1(), 2);
	gamemap.getP1Range(eraser.GetX1(), eraser.GetY1());
	gamemap.getP2Range(play2.GetX1(), play2.GetY1());
	for (int i = 0; i < 4; i++)
	{
		if (gamemap.OnAudio(i) == 1)
		{
			CAudio::Instance()->Play(i+2, false);
			gamemap.ResetAudio(i);
		}
	}
	eraser.SetSpeed(gamemap.set_speed(1));
	play2.SetSpeed(gamemap.set_speed(2));
	gamemap.getP1Range(eraser.GetX1(), eraser.GetY1());
	gamemap.getP2Range(play2.GetX1(), play2.GetY1());
	gamemap.OnMove();
	eraser.SetMap(gamemap.map);
	play2.SetMap(gamemap.map);
	int p1s = gamemap.checkP1Status();
	int p2s = gamemap.checkP2Status();
	if (p2s != 5)
	{
		play2.setP2Status(p2s);
		play2.SetSpeed(2);
	}
	if (p1s != 5)
	{
		eraser.setP1Status(p1s);
		eraser.SetSpeed(2);
	}
	if (p1s == 0 || p2s == 0)
	{
		CAudio::Instance()->Play(AUDIO_DIE, false);
		CAudio::Instance()->Stop(AUDIO_MUSIC);
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	gamemap.LoadBitmap();

	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	//
	// 開始載入資料
	//
	//int i;
	//for (i = 0; i < NUMBALLS; i++)	
	//	ball[i].LoadBitmap();								// 載入第i個球的圖形
	eraser.LoadBitmap();
	play2.LoadBitmap();
	background.LoadBitmap(backmap);		// 載入地圖1的背景圖形
	background2.LoadBitmap(backmap2);	// 載入地圖2的背景圖形
	//
	// 完成部分Loading動作，提高進度
	//
	ShowInitProgress(50);
	practice.LoadBitmap(IDB_BITMAP3);


	hits_left.LoadBitmap();									
	CAudio::Instance()->Load(AUDIO_START,  "sounds\\start.wav");	// 載入編號0的聲音ding.wav
	CAudio::Instance()->Load(AUDIO_MUSIC,  "sounds\\music.wav");// 載入編號1的聲音music.mp3
	CAudio::Instance()->Load(AUDIO_BOBO, "sounds\\bobo.wav");	// 載入編號2的聲音bobo.wav
	CAudio::Instance()->Load(AUDIO_BANG, "sounds\\bang.wav");	// 載入編號3的聲音bang.wav
	CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav");	// 載入編號4的聲音ding2.wav
	CAudio::Instance()->Load(AUDIO_DIE, "sounds\\die.wav");		// 載入編號5的聲音die.wav
	CAudio::Instance()->Load(AUDIO_OVER, "sounds\\over.wav");	// 載入編號6的聲音over.wav

	// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_ENTER = 0x0D;	// keyboard Enter
	const char KEY_Num0 = 0x60;
	
	const char KEY_A = 0x41;		// keyboard A
	const char KEY_W = 0x57;		// keyboard W
	const char KEY_D = 0x44;		// keyboard D
	const char KEY_S = 0x53;		// keyboard S
	const char KEY_SPACE = 0x20; // keyboard空白鍵
	const char KEY_R = 0x52;		// keyboard R
	
	//gamemap.OnKeyDown(nChar, int, int);
	int GetX = eraser.GetX1()/ 70;
	int GetY = eraser.GetY1()/ 70;
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(true);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(true);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(true);
	if (nChar == KEY_ENTER) {
		int Xtest = (eraser.GetX1() + 35) / 70;
		int Ytest = (eraser.GetY1() + 35) / 70;
		//eraser.SetMap(map_init);
		gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
		eraser.SetMap(gamemap.map);
		play2.SetMap(gamemap.map);
	}
	if (nChar == KEY_Num0) {
		int Xtest = (play2.GetX1() + 35) / 70;
		int Ytest = (play2.GetY1() + 35) / 70;
		gamemap.OnKeyDown(nChar, Xtest, Ytest, 1);
		eraser.SetMap(gamemap.map);
		play2.SetMap(gamemap.map);
	}
	if (nChar == KEY_A)
		play2.SetMovingLeft(true);
	if (nChar == KEY_D)
		play2.SetMovingRight(true);
	if (nChar == KEY_W)
		play2.SetMovingUp(true);
	if (nChar == KEY_S)
		play2.SetMovingDown(true);
	if (nChar == KEY_SPACE) {
		int Xtest = (play2.GetX1() + 35) / 70;
		int Ytest = (play2.GetY1() + 35) / 70;
		//eraser.SetMap(map_init);
		gamemap.OnKeyDown(nChar, Xtest, Ytest, 2);
		eraser.SetMap(gamemap.map);
		play2.SetMap(gamemap.map);
	}
	if (nChar == KEY_R) {
		int Xtest = (eraser.GetX1() + 35) / 70;
		int Ytest = (eraser.GetY1() + 35) / 70;
		gamemap.OnKeyDown(nChar, Xtest, Ytest, 2);
		eraser.SetMap(gamemap.map);
		play2.SetMap(gamemap.map);
	}

}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard左箭頭
	const char KEY_UP    = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_A = 0x41; // keyboard A
	const char KEY_W = 0x57; // keyboard W
	const char KEY_D = 0x44; // keyboard D
	const char KEY_S = 0x53; // keyboard S
	if (nChar == KEY_LEFT)
		eraser.SetMovingLeft(false);
	if (nChar == KEY_RIGHT)
		eraser.SetMovingRight(false);
	if (nChar == KEY_UP)
		eraser.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		eraser.SetMovingDown(false);
	if (nChar == KEY_A)
		play2.SetMovingLeft(false);
	if (nChar == KEY_D)
		play2.SetMovingRight(false);
	if (nChar == KEY_W)
		play2.SetMovingUp(false);
	if (nChar == KEY_S)
		play2.SetMovingDown(false);
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
	if (map_mode == 1)
		background.ShowBitmap();			//貼上背景圖
	else
		background2.ShowBitmap();			//貼上背景圖
	
	gamemap.OnShow();

	eraser.OnShow();					// 貼上擦子
	play2.OnShow();
}
}