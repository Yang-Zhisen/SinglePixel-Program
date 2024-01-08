#include <iostream>
#include <opencv2/opencv.hpp>
#include "MvCameraControl.h"
#include"GrabImage.h"
#include"windows.h"
MVImage::MVImage()
{
	//在构造函数里边获取一下相机数量
    memset(&this->m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));//将结构体变量进行初始化，使用memset函数将其内存空间清零，确保咋读都是个0
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);//找出适配的传输设备，此处选择了GigE or USB
    if (MV_OK != nRet)
    {
        std::cout << nRet << std::endl;
    }
    else
    {
        std::cout << "海康相机数量：" << m_stDevList.nDeviceNum << std::endl;
    }
    //相机的初始化

    std::cout << "需要打开的相机序号？";
    std::cin >> this->CamNum;
}

void MVImage::CamInit()
{
    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        DevInfo[i] = m_stDevList.pDeviceInfo[i];
        if (NULL == DevInfo)
        {
            std::cout << "Lost the List!" << std::endl;
            break;
        }
    }
    this->Dev_Open = DevInfo[this->CamNum - 1];
}

void MVImage::OpenCam()
{
    CamInit();
    this->nRet = MV_CC_CreateHandle(&handle, this->Dev_Open);
    if (MV_OK != nRet)
    {
        std::cout << "句柄创建失败！" << std::endl;
        return;
    }

    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK!=nRet) {
        std::cout << "相机打开失败！"<<nRet << std::endl;
        return;
    }
    // 设置触发模式为 软触发
    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 1);
    if (MV_OK != nRet)
    {
        printf("触发模式设置失败");
        return;
    }
	nRet = MV_CC_SetEnumValueByString(handle, "TriggerSource", "Software");
	if (MV_OK != nRet)
	{
		std::cout<<"指定Enum节点设置软触发失败"<<nRet;
		return;
	}


}

void MVImage::CamDisplay() //还没搞清楚俩线程一起的，就在这单独用来注册show的回调吧
{
    nRet = MV_CC_RegisterImageCallBackEx(handle, DisplayCallBack, NULL);//底层直接调用函数,就已经预留出了内容
    if (nRet != MV_OK) {
        std::cout << "回调函数又错了！" << nRet << std::endl;
        return;
    }
}

void MVImage::CloseCam()
{
    //先根据句柄关闭设备
    nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("ClosDevice fail! nRet [0x%x]\n", nRet);
        return;
    }

    // 关闭后销毁句柄
    nRet = MV_CC_DestroyHandle(handle);
    if (MV_OK != nRet)
    {
        printf("Destroy Handle fail! nRet [0x%x]\n", nRet);
        return;
    }
}
bool MVImage::KeyPress()
{
    std::cin >> this->Key;
    if (Key==1)
    {
        return TRUE;
    }
}

void MVImage::ShowImage()
{

    //实时取流
    nRet = MV_CC_StartGrabbing(handle);//开始取流  
    if (nRet == MV_OK)
    {
        std::cout << "相机打开取流成功！" << std::endl;
    }
    //此处有重复调用的问题，因此需要单开用于在循环中一直取流
}


void MVImage::GrabPic()
{
    MV_CC_StopGrabbing(handle);
    MV_CC_StartGrabbing(handle);
    if (KeyPress())
      {
		nRet = MV_CC_SetCommandValue(handle, "TriggerSoftware");
		if (MV_OK != nRet)
		{
            std::cout<<"软触发命令失效！！"<<std::endl;
			return;
		}
       if (MV_CC_GetImageBuffer(handle, &frameInfo, 1000 ) == MV_OK)
            {
                cv::Mat frame(frameInfo.stFrameInfo.nHeight, frameInfo.stFrameInfo.nWidth, CV_8U, frameInfo.pBufAddr);
                // 保存图像到文件夹
                std::string filename = "image_" + std::to_string(frameInfo.stFrameInfo.nFrameNum) + ".jpg";
                std::string filepath = "D:\\SinglePixel\\SinglePixel Program\\imageSet\\" + filename;
                cv::imwrite(filepath, frame);
                std::cout << "保存成功 " << filepath << std::endl;
            }
            else
            {
                std::cout << "取图寄了";
            }
        }
}






