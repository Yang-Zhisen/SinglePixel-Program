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
//        	memset(&this->m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));//���ṹ��������г�ʼ����ʹ��memset���������ڴ�ռ����㣬ȷ��զ�����Ǹ�0
//        	int nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &m_stDevList);//�ҳ�����Ĵ����豸���˴�ѡ����GigE or USB
//        	if (MV_OK != nRet)
//        	{
//        		std::cout<<nRet<<std::endl;
//        	}
//        	else
//        	{
//        		std::cout << "�������������" << m_stDevList.nDeviceNum << std::endl;
//        	}
//            //����ĳ�ʼ��
//            int CamNum;
//            std::cout << "��Ҫ�򿪵������ţ�";
//            std::cin >> CamNum;
//            this->DevInfo_1 = this->m_stDevList.pDeviceInfo[CamNum];//��ȡ���ĳ���豸����Ϣ���������ip���ͺŵ�.
//    }
//    void CmaeraOpen()
//    {
//        if (isOpen)
//        {
//            std::cout << "�Ѿ�������" << std::endl;
//        }
//        nRet = MV_CC_CreateHandle(&handle, DevInfo_1);
//        if (MV_OK != nRet)
//        {
//            std::cout << "�������ʧ�ܣ�" << std::endl;
//            return;
//        }
//        nRet = MV_CC_OpenDevice(handle);
//        if (nRet != MV_OK) {
//            std::cout << "�����ʧ�ܣ�" << std::endl;
//            return;
//        }
//
//        nRet = MV_CC_RegisterImageCallBackEx(handle, ImageCallBack, NULL);//�ײ�ֱ�ӵ��ú���,���Ѿ�Ԥ����������
//        if (nRet != MV_OK) {
//            std::cout << "�ص������ִ��ˣ�" << std::endl;
//            return ;
//        }
//
//        nRet = MV_CC_StartGrabbing(handle);//ץͼ��ʼ��
//        if (nRet == MV_OK)
//        {
//            std::cout << "����򿪳ɹ���" << std::endl;
//        }
//    }
//
//    void TakePicture() {
//        MV_CC_StartGrabbing(handle);//��ץͼ
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
//                // ��ȡͼ��
//                unsigned int* pData = nullptr;
//                MV_FRAME_OUT frameInfo = { 0 };
//                if (MV_CC_GetImageBuffer(handle, &frameInfo, 1000 ) == MV_OK) {
//                    cv::Mat frame(frameInfo.stFrameInfo.nHeight, frameInfo.stFrameInfo.nWidth, CV_8U, frameInfo.pBufAddr);
//
//                    // ����ͼ���ļ���
//                    std::string filename = "image_" + std::to_string(frameInfo.stFrameInfo.nFrameNum) + ".jpg";
//                    std::string filepath = "D:\\SinglePixel\\SinglePixel Program\\imageSet\\" + filename;
//                    cv::imwrite(filepath, frame);
//                    std::cout << "����ɹ� " << filepath << std::endl;
//                }
//                else {
//                    std::cout << "����" << std::endl;
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
//            std::cout << "�ز�����" << std::endl;
//        }
//        MV_CC_CloseDevice(handle);
//        nRet = MV_CC_DestroyHandle(handle);
//        handle = NULL;
//    }
//
//
//    MV_CC_DEVICE_INFO* DevInfo_1;
//    MV_CC_DEVICE_INFO_LIST m_stDevList;             // ch:�豸��Ϣ�б�ṹ������������洢�豸�б�
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