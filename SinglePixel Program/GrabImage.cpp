#include <iostream>
#include <opencv2/opencv.hpp>
#include "MvCameraControl.h"
#include"GrabImage.h"
MVImage::MVImage()
{
	//�����ڹ��캯����߻�ȡһ���������
    memset(&this->m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));//���ṹ��������г�ʼ����ʹ��memset���������ڴ�ռ����㣬ȷ��զ�����Ǹ�0
    int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);//�ҳ�����Ĵ����豸���˴�ѡ����GigE or USB
    if (MV_OK != nRet)
    {
        std::cout << nRet << std::endl;
    }
    else
    {
        std::cout << "�������������" << m_stDevList.nDeviceNum << std::endl;
    }
    //����ĳ�ʼ��

    std::cout << "��Ҫ�򿪵������ţ�";
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






