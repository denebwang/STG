#pragma once
#include "framework.h"
#include "pch.h"
void GetAlpha(CImage& image);	//用于处理图像透明部分
int CalculateFPS();				//计算fps值
int getBGpos(int f);			//用于实现背景滚动效果