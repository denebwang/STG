#pragma once
#include <afxwin.h>
#include"bullet.h"
//玩家类
class Player :
	public CWnd
{
private:
	int xPos;							//坐标
	int yPos;	
	static const float speed;			//玩家移动速度
public:
	Player();
	~Player() {};

	bool slow;							//状态判定
	bool rebirth;
	CImage m_pngPlayer;					//玩家贴图
	CImage m_pngHitbox;					//判定点贴图

	int GetxPos();
	int GetyPos();

	void move();						//移动函数，每帧调用
	double dist(bullet* b);				//获取与子弹的距离
	void death();						//死亡时调用
public:
	DECLARE_MESSAGE_MAP()
};

