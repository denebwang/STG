#include"lib.h"
#include"pch.h"
#include <mmsystem.h>
void GetAlpha(CImage& image)
{
	if (image.GetBPP() == 32)
	{
		int i;
		int j;
		for (i = 0; i < image.GetWidth(); i++)
		{
			for (j = 0; j < image.GetHeight(); j++)
			{
				byte* pByte = (byte*)image.GetPixelAddress(i, j);
				pByte[0] = pByte[0] * pByte[3] / 255;
				pByte[1] = pByte[1] * pByte[3] / 255;
				pByte[2] = pByte[2] * pByte[3] / 255;
			}
		}
	}
}

int CalculateFPS()
{
	static float fps = 0;
	static int frameCount = 0;
	static float currentTime = 0.0f;
	static float lastTime = 0.0f;
	frameCount++;
	currentTime = timeGetTime() / 1000.0f;
	if (currentTime - lastTime > 1.0f)
	{
		fps = frameCount / (currentTime - lastTime);
		lastTime = currentTime;
		frameCount = 0;
	}
	return fps;
}

int getBGpos(int f)
{
	int movespeed = 2;
	int pos = (movespeed * f) % 768;
	return pos;
}