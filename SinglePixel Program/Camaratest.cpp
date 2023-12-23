//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include "MvCameraControl.h"
//
//class MVImage
//{
//public:
//    static void __stdcall ImageCallBack(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser) {
//            cv::Mat frame(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8U, pData);
//            cv::resize(frame, frame, cv::Size(480, 480));
//            cv::imshow("Camera", frame);
//            cv::waitKey(1);
//    }
//
//    MVImage()
//    {
//        	memset(&this->m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));//将结构体变量进行初始化，使用memset函数将其内存空间清零，确保咋读都是个0
//        	int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);//找出适配的传输设备，此处选择了GigE or USB
//        	if (MV_OK != nRet)
//        	{
//        		std::cout<<nRet<<std::endl;
//        	}
//        	else
//        	{
//        		std::cout << "海康相机数量：" << m_stDevList.nDeviceNum << std::endl;
//        	}
//            //相机的初始化
//            int CamNum;
//            std::cout << "需要打开的相机序号？";
//            std::cin >> CamNum;
//            this->DevInfo_1 = this->m_stDevList.pDeviceInfo[CamNum];//获取相机某个设备的信息，这里边有ip，型号等.
//    }
//    void CmaeraOpen()
//    {
//        if (isOpen)
//        {
//            std::cout << "已经带开了" << std::endl;
//        }
//        nRet = MV_CC_CreateHandle(&handle, DevInfo_1);
//        if (MV_OK != nRet)
//        {
//            std::cout << "句柄创建失败！" << std::endl;
//            return;
//        }
//        nRet = MV_CC_OpenDevice(handle);
//        if (nRet != MV_OK) {
//            std::cout << "相机打开失败！" << std::endl;
//            return;
//        }
//
//        nRet = MV_CC_RegisterImageCallBackEx(handle, ImageCallBack, NULL);//底层直接调用函数,就已经预留出了内容
//        if (nRet != MV_OK) {
//            std::cout << "回调函数又错了！" << std::endl;
//            return ;
//        }
//
//        nRet = MV_CC_StartGrabbing(handle);//抓图开始了
//        if (nRet == MV_OK)
//        {
//            std::cout << "相机打开成功！" << std::endl;
//        }
//    }
//
//    void TakePicture() {
//        MV_CC_StartGrabbing(handle);//先抓图
//
//        while (true) {
//            int key = cv::waitKey(0);
//            if (key == 27) {
//                break; 
//            }
//            else if(!NumCharge())  {
//                MV_CC_StopGrabbing(handle);
//                MV_CC_StartGrabbing(handle);
//                std::cout << "Picture taken" << std::endl;
//
//                // 获取图像
//                unsigned int* pData = nullptr;
//                MV_FRAME_OUT frameInfo = { 0 };
//                if (MV_CC_GetImageBuffer(handle, &frameInfo, 1000 ) == MV_OK) {
//                    cv::Mat frame(frameInfo.stFrameInfo.nHeight, frameInfo.stFrameInfo.nWidth, CV_8U, frameInfo.pBufAddr);
//
//                    // 保存图像到文件夹
//                    std::string filename = "image_" + std::to_string(frameInfo.stFrameInfo.nFrameNum) + ".jpg";
//                    std::string filepath = "D:\\SinglePixel\\SinglePixel Program\\imageSet\\" + filename;
//                    cv::imwrite(filepath, frame);
//                    std::cout << "保存成功 " << filepath << std::endl;
//                }
//                else {
//                    std::cout << "寄了" << std::endl;
//                }
//            }
//        }
//    }
//
//    bool NumCharge()
//    {
//        std::string NumCom;
//        std::cin >> NumCom;
//        if (NumCom == "1")
//            return false ;
//        else true;
//    }
//
//    void CmameraClose()
//    {
//        nRet = MV_CC_StopGrabbing(handle);
//        if (nRet != MV_OK) {
//            std::cout << "关不上了" << std::endl;
//        }
//        MV_CC_CloseDevice(handle);
//        nRet = MV_CC_DestroyHandle(handle);
//        handle = NULL;
//    }
//
//
//    MV_CC_DEVICE_INFO* DevInfo_1;
//    MV_CC_DEVICE_INFO_LIST m_stDevList;             // ch:设备信息列表结构体变量，用来存储设备列表
//    void* handle=NULL;
//    int nRet;
//    bool isOpen = false;
//    unsigned int DataSize = 0;
//    unsigned char* pData = nullptr;
//};
//
//int main()
//{
//    MVImage Camera_test;
//        Camera_test.CmaeraOpen();
//        Camera_test.TakePicture();
//        cv::waitKey(0);
//
//    Camera_test.CmameraClose();
//}