#include <iostream>
#include "MvCameraControl.h"
#include"GrabImage.h"
#include"ShowStripe.h"
#include <mutex>
#include<thread>
#include<condition_variable>


std::condition_variable g_cv;
std::mutex g_mutex;

bool SigImg = true;
bool SigGrab = true;
bool Stop = false;


int page = 0;
const float Pi = 3.1415926;
const float Pi_2 = Pi*2;

void GrabImageFunc(MVImage GetImage)
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(g_mutex);
		g_cv.wait(lock, [] { return SigGrab; });
		GetImage.GrabPic(page);
		SigImg = true;
		SigGrab = false;
		g_cv.notify_one();
		
		if (Stop)
		break;
	}
}

//main 就做主线程 用于投图 （opengl所设计的窗口和投图的程序 要求在同一线程下）
int main()
{
	MVImage CamTest;
	CamTest.OpenCam();
	CamTest.ShowImage();

	ShowImage scripe;
	scripe.Getbuffer("vertex.txt", "fragment.txt");
	scripe.ShaderInit();
	scripe.ObjInit();

	std::thread t_Grab(GrabImageFunc, std::ref(CamTest));
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < scripe.height; i++)
		{
			for (int j = 0; j < int(scripe.wide / 2) + 1; j++)
			{
				if (scripe.Input())
					break;
				std::unique_lock<std::mutex>lock(g_mutex);
				float fx[3] = { i * Pi_2 / scripe.wide,j * Pi_2 / scripe.height,k * Pi / 2 };
				scripe.DrawStride(fx);
				page += 1;
				SigImg = false;
				SigGrab = true;
				g_cv.notify_one();
				g_cv.wait(lock, [] {return SigImg; });
				
			}
		}
	}
	Stop = true;
	t_Grab.join();
}
