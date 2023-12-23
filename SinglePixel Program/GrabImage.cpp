#include <iostream>
#include <opencv2/opencv.hpp>
#include "MvCameraControl.h"
#include"GrabImage.h"
MVImage::MVImage()
{
	//依旧在构造函数里边获取一下相机数量
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

MV_CC_DEVICE_INFO* MVImage::CamInit()
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
    this->Dev_Open = this->DevInfo[this->CamNum - 1];
}

void MVImage::OpenCam()
{

}






