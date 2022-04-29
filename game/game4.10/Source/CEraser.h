namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////
	static int map_init[13][15] = {
	{0, 0, 4, 5, 4, 8, 0, 0, 6, 8, 2, 5, 2, 0, 2},
	{0, 1, 6, 1, 6, 7, 6, 0, 0, 7, 4, 5, 4, 0, 0},
	{5, 4, 5, 4, 5, 8, 0, 6, 6, 8, 2, 6, 2, 6, 2},
	{6, 1, 6, 1, 6, 7, 6, 0, 0, 7, 5, 4, 5, 4, 5},
	{4, 5, 4, 5, 4, 8, 0, 0, 6, 8, 2, 6, 2, 6, 2},
	{5, 1, 5, 1, 5, 7, 6, 6, 0, 7, 4, 5, 4, 5, 4},
	{7, 8, 7, 8, 7, 8, 0, 0, 6, 8, 7, 8, 7, 8, 7},
	{4, 5, 4, 5, 4, 7, 6, 0, 0, 7, 4, 1, 4, 1, 4},
	{3, 6, 3, 6, 3, 8, 0, 6, 6, 8, 5, 4, 5, 4, 5},
	{5, 4, 5, 4, 5, 7, 6, 0, 0, 7, 6, 1, 6, 1, 6},
	{3, 6, 3, 6, 3, 8, 0, 0, 6, 8, 4, 5, 4, 5, 4},
	{0, 0, 4, 5, 4, 7, 6, 6, 0, 7, 6, 1, 6, 1, 0},
	{3, 0, 3, 4, 3, 8, 0, 0, 6, 8, 5, 4, 5, 0, 0} };
	class CEraser
	{
	public:
		CEraser();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void SetMap(int map[13][15]);
	protected:
		//CAnimation animation;		// 擦子的動畫
		CMovingBitmap P1_down, P1_up, P1_left, P1_right;
		int x, y, mode;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
	};
}