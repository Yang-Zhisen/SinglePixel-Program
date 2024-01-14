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


//线程通信的小例子 后续可改进线程通信
//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <queue>
//std::mutex g_mutex;
//std::mutex g_mutex2;
//std::condition_variable g_cv;
//std::condition_variable g_cv2;
//std::queue<int> g_queue;
//
//void Producer() {
//	for (int i = 0; i < 10; i++) {
//		{
//			std::unique_lock<std::mutex> lock(g_mutex);
//			g_queue.push(i);
//			std::cout << "Producer: produced " << i << std::endl;
//		}
//		std::unique_lock<std::mutex> lock2(g_mutex2);
//		g_cv.notify_one();
//		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
//		g_cv2.wait(lock2);
//	}
//}
//void Consumer() {
//	while (true) {
//		std::unique_lock<std::mutex> lock(g_mutex);
//		g_cv.wait(lock, []() { return !g_queue.empty(); });
//		int value = g_queue.front();
//		g_queue.pop();
//		std::cout << "Consumer: consumed " << value << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//		std::unique_lock<std::mutex> lock2(g_mutex2);
//		g_cv2.notify_one();
//	}
//}
//int main2() {
//	std::thread producer_thread(Producer);
//	std::thread consumer_thread(Consumer);
//	producer_thread.detach();
//	consumer_thread.join();
//	return 0;
//}
