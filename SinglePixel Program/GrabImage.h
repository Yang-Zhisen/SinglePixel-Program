#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "MvCameraControl.h"

class MVImage
{
public:
	void OpenCam();
	MVImage();
	void ShowImage();
	void CloseCam();
	bool KeyPress();
	void   GrabPic();
	void CamDisplay();

	
private:
	MV_FRAME_OUT frameInfo = { 0 };
	int Key;
	int nRet = MV_OK;
	void* handle = NULL;
	static void __stdcall DisplayCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser) {
		cv::Mat frame(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8U, pData);
		cv::resize(frame, frame, cv::Size(480, 480));
		cv::imshow("Camera", frame);
		cv::waitKey(1);

		//我在创建回调函数只后，相机抓图就会调用，那参数传入是自分配？ pUser用户自定义变量 意义？常规？
 }
	 



	MV_CC_DEVICE_INFO* DevInfo[10];
	MV_CC_DEVICE_INFO* Dev_Open;
	MV_CC_DEVICE_INFO_LIST m_stDevList;             // ch:设备信息列表结构体变量，用来存储设备列表
	int CamNum;
	void CamInit();


};


