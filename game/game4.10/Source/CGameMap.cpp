#include "StdAfx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"
#include <stdlib.h>





/*
	炸彈延時設置 sleep variable, 炸彈地圖, 判斷炸彈連結
	1. 判斷當前區域為可否破壞物(樹木,房子不可破壞),人 and 積木可破壞, 碰到人殺人
	2. 如果是碰到炸彈 刷新炸彈時間 從而實現連環爆炸
	3. 根據當前位置放圖片
	4. 提升炸彈能力
	5. 盒子破壞後的道具
	6. 給爆炸加聲音


	代辦:
		檢測爆炸碰到人
		做2個陣列存取 每個炸彈時間 爆炸畫面計時陣列

*/


namespace game_framework {

	CGameMap::CGameMap()
		:X(0), Y(0), MW(70), MH(70)
	{

		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				map[i][j] = map_init[i][j];
				mapCopy[i][j] = map_init[i][j];
				bombMap[i][j] = map_bomb[i][j];
				idMap[i][j] = map_id[i][j];
				exp_Map[i][j] = map_explosion[i][j];
				
			}
		}
		timer = 6, timerS = 30;
		audio[0] = 0, audio[1] = 0, audio[2] = 0, audio[3] = 0;
		p1_distance = 1, p1_quantity = 1, p1_speed = 10;
		p2_distance = 1, p2_quantity = 1, p2_speed = 10;
		p1Status = 5, p2Status = 5;
		hitP1 = false, hitP2 = false;
		//角色初始值設定
	}

	// 缺炸毀建築 炸到玩家
	void CGameMap::set_expMap()
	{
		int k = 0;

		//int count = 0;
		//bool flag = false
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (bombMap[i][j] == 1)
				{
					int temp = 0;
					// 獲取炸彈爆炸範圍
					if (idMap[i][j] == 1)
					{
						temp = p1_distance;
					}
					else
					{
						temp = p2_distance;
					}

					for (k = 1; k <= temp; k++)
					{
						if (i + k < 13) {
							if (map[i + k][j] == 0)
							{
								if (k != temp)
								{
									exp_Map[i + k][j] = 3;
								}
								else
								{
									exp_Map[i + k][j] = 4;
									break;
								}

							}
							else// 無障礙
							{
								exp_Map[i + k - 1][j] = 4;
								break;
							}
						}
						else
						{
							break;
						}
					}

					for (k = 0; k <= temp; k++)
					{
						if (exp_Map[i + k][j] == 4 && (i + k) < 13 && k != temp)
						{
							int random_num = (rand() % 6);
							if ((map[i + k + 1][j] > 4 && map[i + k + 1][j] < 9) || map[i + k + 1][j] > 14)
							{
								if (random_num < 3 || map[i + k + 1][j] >= 20)
									mapCopy[i + k + 1][j] = 0;
								else if (random_num == 3)
									mapCopy[i + k + 1][j] = 21;
								else if (random_num == 4)
									mapCopy[i + k + 1][j] = 22;
								else if (random_num == 5)
									mapCopy[i + k + 1][j] = 23;
							}
						}
					}
					//開找3 4




					for (k = 1; k <= temp; k++)
					{
						if (i - k >= 0) {
							if (map[i - k][j] == 0)
							{
								if (k != temp)
								{
									exp_Map[i - k][j] = 1;
								}
								else
								{
									exp_Map[i - k][j] = 2;
									break;
								}
							}
							else
							{
								exp_Map[i - k + 1][j] = 2;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (k = 0; k <= temp; k++)
					{
						if (exp_Map[i - k][j] == 2 && (i - k) >= 0 && k != temp)
						{
							int random_num = (rand() % 6);
							if ((map[i - k - 1][j] > 4 && map[i - k - 1][j] < 9) || map[i - k - 1][j] > 14)
							{
								if (random_num < 3 || map[i - k - 1][j] >= 20)
									mapCopy[i - k - 1][j] = 0;
								else if (random_num == 3)
									mapCopy[i - k - 1][j] = 21;
								else if (random_num == 4)
									mapCopy[i - k - 1][j] = 22;
								else if (random_num == 5)
									mapCopy[i - k - 1][j] = 23;
							}
						}
					}

					for (k = 1; k <= temp; k++)
					{
						if (j + k < 15)
						{
							if (map[i][j + k] == 0)
							{
								if (k != temp)
								{
									exp_Map[i][j + k] = 7;
								}
								else
								{
									exp_Map[i][j + k] = 8;
									break;
								}
							}
							else
							{
								exp_Map[i][j + k - 1] = 8;
								break;
							}
						}
						else
						{
							break;
						}
					}

					for (k = 0; k <= temp; k++)
					{

						if (exp_Map[i][j + k] == 8 && (j + k) < 15 && k != temp)
						{
							int random_num = (rand() % 6);
							if ((map[i][j + k + 1] > 4 && map[i][j + k + 1] < 9) || map[i][j + k + 1] > 14)
							{
								if (random_num < 3 || map[i][j + k + 1] >= 20)
									mapCopy[i][j + k + 1] = 0;
								else if (random_num == 3)
									mapCopy[i][j + k + 1] = 21;
								else if (random_num == 4)
									mapCopy[i][j + k + 1] = 22;
								else if (random_num == 5)
									mapCopy[i][j + k + 1] = 23;
							}
						}
					}

					for (k = 1; k <= temp; k++)
					{
						if (j - k >= 0)
						{
							if (map[i][j - k] == 0)
							{
								if (k != temp)
								{
									exp_Map[i][j - k] = 5;
								}
								else
								{
									exp_Map[i][j - k] = 6;
									break;
								}
							}
							else
							{
								exp_Map[i][j - k + 1] = 6;
								break;
							}
						}
						else
						{
							break;
						}
					}
					for (k = 0; k <= temp; k++)
					{

						if (exp_Map[i][j - k] == 6 && (j - k) >= 0 && k != temp)
						{
							int random_num = (rand() % 6);
							if ((map[i][j - k - 1] > 4 && map[i][j - k - 1] < 9) || map[i][j - k - 1] > 14)
							{
								if (random_num < 3 || map[i][j - k - 1] >= 20)
									mapCopy[i][j - k - 1] = 0;
								else if (random_num == 3)
									mapCopy[i][j - k - 1] = 21;
								else if (random_num == 4)
									mapCopy[i][j - k - 1] = 22;
								else if (random_num == 5)
									mapCopy[i][j - k - 1] = 23;
							}
						}
					}
				}
			}
		}
	}
	void CGameMap::updateMap()
	{
		if (timer % 7 == 0)
		{
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 15; j++)
				{
					map[i][j] = mapCopy[i][j];
				}
		}
	}

	void CGameMap::setDistance(int player)
	{
		if (player == 1)
			p1_distance += 1;
		else if (player == 2)
			p2_distance += 1;

	}

	void CGameMap::setLinkBomb()
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 15; j++)
			{
				int id = idMap[i][j];
				if (bombMap[i][j] > 0 && id == 1)
				{
					for (int k = 1; k <= p1_distance; k++)
					{
						if (map[i + k][j] == 0)
						{
							if (bombMap[i + k][j] > bombMap[i][j] && idMap[i + k][j] == 1)
							{
								bombMap[i + k][j] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}

					for (int k = 1; k <= p1_distance; k++)
					{
						if (map[i - k][j] == 0)
						{
							if (bombMap[i - k][j] > bombMap[i][j] && idMap[i - k][j] == 1)
							{
								bombMap[i - k][j] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= p1_distance; k++)
					{
						if (map[i][j + k] == 0)
						{
							if (bombMap[i][j + k] > bombMap[i][j] && idMap[i][j + k] == 1)
							{
								bombMap[i][j + k] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}
					for (int k = 1; k <= p1_distance; k++)
					{
						if (map[i][j - k] == 0)
						{
							if (bombMap[i][j - k] > bombMap[i][j] && idMap[i][j - k] == 1)
							{
								bombMap[i][j - k] = bombMap[i][j];
							}
						}
						else
						{
							break;
						}
					}
				}

				else if (bombMap[i][j] > 0 && id == 2)
				{
					for (int k = 1; k <= p2_distance; k++)
					{
						if (bombMap[i + k][j] > bombMap[i][j] && idMap[i + k][j] == 2)
						{
							bombMap[i + k][j] = bombMap[i][j];
						}
					}

					for (int k = 1; k <= p2_distance; k++)
					{
						if (bombMap[i - k][j] > bombMap[i][j] && idMap[i - k][j] == 2)
						{
							bombMap[i - k][j] = bombMap[i][j];
						}
					}
					for (int k = 1; k <= p2_distance; k++)
					{
						if (bombMap[i][j + k] > bombMap[i][j] && idMap[i][j + k] == 2)
						{
							bombMap[i][j + k] = bombMap[i][j];
						}
					}
					for (int k = 1; k <= p2_distance; k++)
					{
						if (bombMap[i][j - k] > bombMap[i][j] && idMap[i][j - k] == 2)
						{
							bombMap[i][j - k] = bombMap[i][j];
						}
					}
				}

			}
	}


	void CGameMap::getP1Range(int x1, int y1)
	{
		X1_1 = x1, Y1_1 = y1;
	}

	void CGameMap::getP2Range(int x1, int y1)
	{
		X1_2 = x1, Y1_2 = y1;
	}

	void CGameMap::hitWater()
	{
		if (exp_Map[(Y1_1 + 47) / 70][(X1_1 + 35) / 70] != 0) {
			hitP1 = true;
		}
		if (exp_Map[(Y1_2 + 47) / 70][(X1_2 + 35) / 70] != 0 ) {
			hitP2 = true;
		}
	}
	int CGameMap::checkP1Status()
	{
		return p1Status;
	}
	int CGameMap::checkP2Status()
	{
		return p2Status;
	}
	void CGameMap::checkHitP1()
	{
		if (hitP1 == true)
		{
			if (timerS % 31 == 0)
			{
				p1Status--;
			}
		}
	}
	void CGameMap::checkHitP2()
	{
		if (hitP2 == true)
		{
			if (timerS % 31 == 0)
			{
				p2Status--;
			}
		}
	}

	void CGameMap::OnKeyDown(UINT nChar, int Xtest, int Ytest, int id)
	{
		const char KEY_SPACE = 0x20;
		const char KEY_Num0 = 0x60;	//玩家1密技 殺死玩家2
		const char KEY_R = 0x52;	//玩家2密技 殺死玩家1
		const char KEY_E = 0x45;
		if (nChar == KEY_SPACE)
		{
			if (map[Ytest][Xtest] == 0 && bombMap[Ytest][Xtest] == 0 && p1_quantity > 0 && id == 1)
			{
				p1_quantity -= 1;
				bombMap[Ytest][Xtest] = 11;
				idMap[Ytest][Xtest] = 1;
				audio[0] = 1;
				mapCopy[Ytest][Xtest] = 10;
			}
		}
		if (nChar == KEY_E)
		{
			if (map[Ytest][Xtest] == 0 && bombMap[Ytest][Xtest] == 0 && p2_quantity > 0 && id == 2)
			{
				p2_quantity -= 1;
				bombMap[Ytest][Xtest] = 11;
				idMap[Ytest][Xtest] = 2;
				audio[0] = 1;
				mapCopy[Ytest][Xtest] = 10;
			}
		}
		if (nChar == KEY_R)
		{
			if (map[Ytest - 1][Xtest] == 0) {
				bombMap[Ytest - 1][Xtest] = 11;
				mapCopy[Ytest - 1][Xtest] = 10;
			}
			if (map[Ytest + 1][Xtest] == 0) {
				bombMap[Ytest + 1][Xtest] = 11;
				mapCopy[Ytest + 1][Xtest] = 10;
			}
			if (map[Ytest][Xtest - 1] == 0) {
				bombMap[Ytest][Xtest - 1] = 11;
				mapCopy[Ytest][Xtest - 1] = 10;
			}
			if (map[Ytest][Xtest + 1] == 0) {
				bombMap[Ytest][Xtest + 1] = 11;
				mapCopy[Ytest][Xtest + 1] = 10;
			}
			audio[0] = 1;
		}
	}
	void CGameMap::OnProps(int X1, int Y1, int id)
	{
		if (mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] == 21 && id == 1) {
			mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] = 0;
			if (p1_quantity < 5)
				p1_quantity += 1;
			audio[2] = 1;
		}
		else if (mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] == 22 && id == 1) {
			mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] = 0;
			if (p1_distance < 7)
				p1_distance += 1;
			audio[2] = 1;
		}
		else if (mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] == 23 && id == 1) {
			mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] = 0;
			if (p1_speed < 20)
				p1_speed += 2;
			audio[2] = 1;
		}
		//-----------------------------------------------------------//
		if (mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] == 21 && id == 2) {
			mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] = 0;
			if (p2_quantity < 5)
				p2_quantity += 1;
			audio[2] = 1;
		}
		else if (mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] == 22 && id == 2) {
			mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] = 0;
			if (p2_distance < 7)
				p2_distance += 1;
			audio[2] = 1;
		}
		else if (mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] == 23 && id == 2) {
			mapCopy[(Y1 + 47) / 70][(X1 + 35) / 70] = 0;
			if (p2_speed < 20)
				p2_speed += 2;
			audio[2] = 1;
		}
	}
	bool CGameMap::OnAudio(int mode)
	{
		if (mode == 0)
			return audio[0];
		else if (mode == 1)
			return audio[1];
		else if (mode == 2)
			return audio[2];
		else if (mode == 3)
			return audio[3];
		else
			return 0;
	}
	void CGameMap::ResetAudio(int mode)
	{
		for (int i = 0; i < 4; i++)
		{
			if (mode == i)
				audio[i] = 0;
		}
	}
	int CGameMap::set_speed(int player)
	{
		if (player == 1)
			return p1_speed;
		else if (player == 2)
			return p2_speed;
		else
			return 0;
	}
	void CGameMap::setBombInfo()
	{
		if (timer % 7 == 0)
		{
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 15; j++)
				{
					if (bombMap[i][j] > 2)
					{
						bombMap[i][j]--;
					}
					else if (bombMap[i][j] == 2)
					{
						bombMap[i][j]--;
						audio[1] = 1;
					}
					else if (bombMap[i][j] == 1)
					{
						bombMap[i][j]--;
						mapCopy[i][j] = 0;
						p1_quantity += 1;
						//                          yo yo yo 我在這 這裡是被我臨時放來回復 p2_quantity 的 需要你來搞 甘溫
						p2_quantity += 1;
						//audio[1] = 1;
					}
				}
		}
	}
	void CGameMap::set_map(int mode)
	{
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				if (mode == 1)
				{
					map[i][j] = map_init[i][j];
					mapCopy[i][j] = map_init[i][j];
				}
				else if(mode == 2)
				{
					map[i][j] = map2_init[i][j];
					mapCopy[i][j] = map2_init[i][j];
				}
			}
		}
	}
	void CGameMap::OnMove()
	{
		timer--;	// 計時
		timerS--;
		/*
		for (int i = 0; i < random_num; i++)
		{
			bballs[i].OnMove();
		}*/
		AnimationBomb.OnMove();
		if (timer == -1)
			timer = 6;	// 復原計時
		if (timerS == -1)
			timer = 30;

		setBombInfo();	// 裝炸彈
		setLinkBomb();	// 設定連鎖
		updateMap();
		set_expMap();
		hitWater();
		checkHitP1();
		checkHitP2();


	}



	CGameMap::~CGameMap()
	{
	}
	void CGameMap::LoadBitmap()
	{
		House_r.LoadBitmap(house_r, RGB(255, 255, 255));		//1
		House_y.LoadBitmap(house_y, RGB(255, 255, 255));		//2
		House_b.LoadBitmap(house_b, RGB(255, 255, 255));		//3
		Tree.LoadBitmap(tree, RGB(255, 255, 255));				//4
		Blocks_r.LoadBitmap(blocks_r, RGB(255, 255, 255));		//5
		Blocks_y.LoadBitmap(blocks_y, RGB(255, 255, 255));		//6
		Wooden_box.LoadBitmap(wooden_box, RGB(255, 255, 255));	//7
		Grass.LoadBitmap(grass, RGB(255, 255, 255));			//8

		Green_box.LoadBitmap(green_box, RGB(255, 255, 255));	//11
		Green_box2.LoadBitmap(green_box2, RGB(255, 255, 255));	//12
		Rock.LoadBitmap(rock, RGB(255, 255, 255));				//13
		Cactus.LoadBitmap(cactus, RGB(255, 255, 255));			//14
		Earth.LoadBitmap(earth, RGB(255, 255, 255));			//15
		Tent_b.LoadBitmap(tent_b, RGB(255, 255, 255));			//16
		Tent_r.LoadBitmap(tent_r, RGB(255, 255, 255));			//17
		Tent_y.LoadBitmap(tent_y, RGB(255, 255, 255));			//18

		Props_1.LoadBitmap(props_1, RGB(255, 255, 255));		//21
		Props_2.LoadBitmap(props_2, RGB(255, 255, 255));		//22
		Props_3.LoadBitmap(props_3, RGB(255, 255, 255));		//23

		NULLNULL.LoadBitmap(bull, RGB(255, 255, 255));	//空方塊(用來填充放置水球的地方)
		Bomb.LoadBitmap(bomb, RGB(255, 255, 255));		//水球1狀態
		Bomb2.LoadBitmap(bomb2, RGB(255, 255, 255));	// 水球2狀態
		Bomb3.LoadBitmap(bomb3, RGB(255, 255, 255));	// 水球3狀態

		explode.LoadBitmap(".\\res\\explode.bmp", RGB(255, 255, 255));



		char* filename[3] = { ".\\res\\bomb.bmp",".\\res\\bomb2.bmp",".\\res\\explode.bmp" };
		for (int i = 0; i < 3; i++)	// 載入動畫(由4張圖形構成)
		{
			AnimationBomb.AddBitmap(filename[i], RGB(255, 255, 255));
			AnimationBomb.SetDelayCount(25);
		}
		testforbomb.AddBitmap(".\\res\\bomb2.bmp", RGB(255, 255, 255));
		testforbomb.SetDelayCount(25);

		testforbomb2.AddBitmap(".\\res\\explode.bmp", RGB(255, 255, 255));
		testforbomb2.SetDelayCount(25);

		w_R.AddBitmap(".\\res\\water_right.bmp", RGB(255, 255, 255));
		//w_R.SetDelayCount(25);

		w_R_E.AddBitmap(".\\res\\water_right_end.bmp", RGB(255, 255, 255));
		//w_R_E.SetDelayCount(25);

		w_L.AddBitmap(".\\res\\water_left.bmp", RGB(255, 255, 255));
		//w_L.SetDelayCount(25);

		w_L_E.AddBitmap(".\\res\\water_left_end.bmp", RGB(255, 255, 255));
		//w_L_E.SetDelayCount(25);

		w_U.AddBitmap(".\\res\\water_up.bmp", RGB(255, 255, 255));
		//w_U.SetDelayCount(25);

		w_U_E.AddBitmap(".\\res\\water_up_end.bmp", RGB(255, 255, 255));
		//w_U_E.SetDelayCount(25);

		w_D.AddBitmap(".\\res\\water_down.bmp", RGB(255, 255, 255));
		//w_D.SetDelayCount(25);

		w_D_E.AddBitmap(".\\res\\water_down_end.bmp", RGB(255, 255, 255));
		//w_D_E.SetDelayCount(25);

	}


	void CGameMap::OnShow()
	{
		/*
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 15; j++) {
				map[i][j] = map_init[i][j];
			}
		}*/

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 13; j++) {
				switch (bombMap[j][i]) {
				case 0:
					break;
				case 11:
					Bomb3.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb3.ShowBitmap();
					break;
				case 10:
					Bomb.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb.ShowBitmap();
					break;
				case 9:
					Bomb2.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb2.ShowBitmap();
					break;
				case 8:
					Bomb.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb.ShowBitmap();
					break;
				case 7:
					Bomb3.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb3.ShowBitmap();
					break;
				case 6:
					Bomb.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb.ShowBitmap();
					break;
				case 5:
					Bomb2.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb2.ShowBitmap();
					break;
				case 4:
					Bomb.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb.ShowBitmap();
					break;
				case 3:
					Bomb3.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb3.ShowBitmap();
					break;
				case 2:
					Bomb.SetTopLeft(X + (MW * i), Y + (MH * j));
					Bomb.ShowBitmap();
					break;
				case 1:
					explode.SetTopLeft(X + (MW * i), Y + (MH * j));
					explode.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 13; j++) {
				switch (map[j][i]) {
				case 0:
					break;
				//村莊地圖
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
					Tree.SetTopLeft(X + (MW * i), Y + (MH * j));
					Tree.ShowBitmap();
					break;
				case 5:
					Blocks_r.SetTopLeft(X + (MW * i), Y + (MH * j));
					Blocks_r.ShowBitmap();
					break;
				case 6:
					Blocks_y.SetTopLeft(X + (MW * i), Y + (MH * j));
					Blocks_y.ShowBitmap();
					break;
				case 7:
					Wooden_box.SetTopLeft(X + (MW * i), Y + (MH * j));
					Wooden_box.ShowBitmap();
					break;
				case 8:
					Grass.SetTopLeft(X + (MW * i), Y + (MH * j));
					Grass.ShowBitmap();
					break;
				//沙漠地圖
				case 11:
					Green_box.SetTopLeft(X + (MW * i), Y + (MH * j));
					Green_box.ShowBitmap();
					break;
				case 12:
					Green_box2.SetTopLeft(X + (MW * i), Y + (MH * j));
					Green_box2.ShowBitmap();
					break;
				case 13:
					Rock.SetTopLeft(X + (MW * i), Y + (MH * j));
					Rock.ShowBitmap();
					break;
				case 14:
					Cactus.SetTopLeft(X + (MW * i), Y + (MH * j));
					Cactus.ShowBitmap();
					break;
				case 15:
					Earth.SetTopLeft(X + (MW * i), Y + (MH * j));
					Earth.ShowBitmap();
					break;
				case 16:
					Tent_b.SetTopLeft(X + (MW * i), Y + (MH * j));
					Tent_b.ShowBitmap();
					break;
				case 17:
					Tent_r.SetTopLeft(X + (MW * i), Y + (MH * j));
					Tent_r.ShowBitmap();
					break;
				case 18:
					Tent_y.SetTopLeft(X + (MW * i), Y + (MH * j));
					Tent_y.ShowBitmap();
					break;
				//NULL
				case 10:
					NULLNULL.SetTopLeft(X + (MW * i), Y + (MH * j));
					NULLNULL.ShowBitmap();
					break;
				//道具
				case 21:
					Props_1.SetTopLeft(X + (MW * i) + 5, Y + (MH * j));
					Props_1.ShowBitmap();
					break;
				case 22:
					Props_2.SetTopLeft(X + (MW * i) + 5, Y + (MH * j));
					Props_2.ShowBitmap();
					break;
				case 23:
					Props_3.SetTopLeft(X + (MW * i) + 5, Y + (MH * j));
					Props_3.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 13; j++) {
				switch (exp_Map[j][i]) {
				case 0:
					break;
				case 1:
					w_U.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_U.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}

					break;
				case 2:
					w_U_E.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_U_E.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 3:
					w_D.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_D.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 4:
					w_D_E.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_D_E.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 5:
					w_L.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_L.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 6:
					w_L_E.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_L_E.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 7:
					w_R.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_R.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
				case 8:
					w_R_E.SetTopLeft(X + (MW * i), Y + (MH * j));
					w_R_E.OnShow();
					if (timer % 7 == 0)
					{
						exp_Map[j][i] = 0;
					}
					break;
					//case 9:
					//	w_U.SetTopLeft(X + (MW * i), Y + (MH * j));
					//	w_U.OnShow();
					//	break;
				default:
					ASSERT(0);
				}
			}


		CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
		CFont f, * fp;
		f.CreatePointFont(160, "Times New Roman");	// 產生 font f; 160表示16 point的字
		fp = pDC->SelectObject(&f);					// 選用 font f
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 255, 0));

		CString str;
		str.Format(_T("%d"), p1Status);
		pDC->TextOut(120, 220, str);
		//pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");
		//if (ENABLE_GAME_PAUSE)
			//pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");
		//pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
		//pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
		CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC

		/* 原本練習的map 的 ball
		for (int i = 0; i < random_num; i++) {
			bballs[i].OnShow();
		}*/
	}
}