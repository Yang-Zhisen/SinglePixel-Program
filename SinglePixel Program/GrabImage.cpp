#include <iostream>
#include <opencv2/opencv.hpp>
#include "MvCameraControl.h"
#include"GrabImage.h"
#include"windows.h"
MVImage::MVImage()
{
	//�ڹ��캯����߻�ȡһ���������
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
        std::cout << "�������ʧ�ܣ�" << std::endl;
        return;
    }

    nRet = MV_CC_OpenDevice(handle);
    if (MV_OK!=nRet) {
        std::cout << "�����ʧ�ܣ�"<<nRet << std::endl;
        return;
    }
    // ���ô���ģʽΪ ����
    nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 1);
    if (MV_OK != nRet)
    {
        printf("����ģʽ����ʧ��");
        return;
    }
	nRet = MV_CC_SetEnumValueByString(handle, "TriggerSource", "Software");
	if (MV_OK != nRet)
	{
		std::cout<<"ָ��Enum�ڵ���������ʧ��"<<nRet;
		return;
	}


}

void MVImage::CamDisplay() //��û��������߳�һ��ģ������ⵥ������ע��show�Ļص���
{
    nRet = MV_CC_RegisterImageCallBackEx(handle, DisplayCallBack, NULL);//�ײ�ֱ�ӵ��ú���,���Ѿ�Ԥ����������
    if (nRet != MV_OK) {
        std::cout << "�ص������ִ��ˣ�" << nRet << std::endl;
        return;
    }
}

void MVImage::CloseCam()
{
    //�ȸ��ݾ���ر��豸
    nRet = MV_CC_CloseDevice(handle);
    if (MV_OK != nRet)
    {
        printf("ClosDevice fail! nRet [0x%x]\n", nRet);
        return;
    }

    // �رպ����پ��
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

    //ʵʱȡ��
    nRet = MV_CC_StartGrabbing(handle);//��ʼȡ��  
    if (nRet == MV_OK)
    {
        std::cout << "�����ȡ���ɹ���" << std::endl;
    }
    //�˴����ظ����õ����⣬�����Ҫ����������ѭ����һֱȡ��
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
            std::cout<<"��������ʧЧ����"<<std::endl;
			return;
		}
       if (MV_CC_GetImageBuffer(handle, &frameInfo, 1000 ) == MV_OK)
            {
                cv::Mat frame(frameInfo.stFrameInfo.nHeight, frameInfo.stFrameInfo.nWidth, CV_8U, frameInfo.pBufAddr);
                // ����ͼ���ļ���
                std::string filename = "image_" + std::to_string(frameInfo.stFrameInfo.nFrameNum) + ".jpg";
                std::string filepath = "D:\\SinglePixel\\SinglePixel Program\\imageSet\\" + filename;
                cv::imwrite(filepath, frame);
                std::cout << "����ɹ� " << filepath << std::endl;
            }
            else
            {
                std::cout << "ȡͼ����";
            }
        }
}






