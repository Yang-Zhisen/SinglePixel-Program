#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include "MvCameraControl.h"

class MVImage
{
public:
	void OpenCam();
	MVImage();


private:
	MV_CC_DEVICE_INFO* DevInfo[100];
	MV_CC_DEVICE_INFO* Dev_Open;
	MV_CC_DEVICE_INFO_LIST m_stDevList;             // ch:设备信息列表结构体变量，用来存储设备列表
	int CamNum;
	MV_CC_DEVICE_INFO* CamInit();

};


