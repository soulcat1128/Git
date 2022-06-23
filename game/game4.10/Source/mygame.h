#include "CEraser.h"
#include "Play2.h"
//#include "CBall.h"
#include "CGameMap.h"
// #include "CBouncingBall.h"

namespace game_framework {

	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_START,			// 0
		AUDIO_MUSIC,			// 1
		AUDIO_BOBO,				// 2
		AUDIO_BANG,				// 3
		AUDIO_DING,				// 4
		AUDIO_DIE,				// 5
		AUDIO_OVER				// 6
	};

	static int map_mode;

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame* g);						
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		//void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo,Operate;								// csie的logo
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////
	class CPractice {
	public:
		CPractice();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		CMovingBitmap pic;
		int x, y;
	};
	class CBouncingBall
	{
	public:
		CBouncingBall();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetFloor(int);
		void SetXY(int, int);
		void SetVelocity(int);
	private:
		int x, y;
		int floor;
		bool rising;
		int initial_velocity;
		int velocity;
		CAnimation animation;
	};
		

	
	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CGameMap	gamemap;
		// CGameMap	upperMap(bool flag  = true);
		CPractice c_practice;
		CMovingBitmap practice;
		int picX, picY;
		const int		NUMBALLS;	// 球的總數
		CMovingBitmap	background, background2;	// 背景圖
		CMovingBitmap	help;		// 說明圖
		// CBall* ball;		// 球的陣列
		CMovingBitmap	corner;		// 角落圖
		CEraser			eraser;		// 角色
		Play2			play2;
		CInteger		hits_left;	// 剩下的撞擊數
		CBouncingBall   bball;		// 反覆彈跳的球
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;	// 倒數之計數器
	};

}