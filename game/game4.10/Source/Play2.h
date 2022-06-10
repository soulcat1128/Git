#include "CGameMap.h"
namespace game_framework {

	class Play2 //:public CGameMap
	{
	public:
		Play2();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void Initialize();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		void SetMovingDown(bool flag);	
		void SetMovingLeft(bool flag);	
		void SetMovingRight(bool flag); 
		void SetMovingUp(bool flag);	
		void SetXY(int nx, int ny);		
		int map_user[13][15];
		void SetMap(int map[13][15]);
		int speed;
		int status;
		bool isAlive;
		int explosionRange;
	protected:
		CMovingBitmap P2_down, P2_up, P2_left, P2_right;
		int x, y,mode;
		bool isMovingDown;
		bool isMovingLeft;
		bool isMovingRight;
		bool isMovingUp;
	};
}