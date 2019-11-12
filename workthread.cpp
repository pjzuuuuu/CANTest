#include "workthread.h"

WorkThread::WorkThread(QObject *parent):QThread(parent)
{
//    DeviceType = deviceType;
//    DeviceInd = deviceInd;
//    CANInd = canInd;
//    CANMode = canMode;
    ThStart = true;
    BUFLEN = 10;
}


int WorkThread::StartCan()
{
    HANDLE Status = VCI_OpenDevice(DeviceType,DeviceInd,0);
    if(Status > 0)
    {
        switch (DeviceType) {
        case VCI_CANETTCP:
        {
            if(CANMode == 0)
            {
                VCI_SetReference(DeviceType,DeviceInd,CANInd,0,(PVOID) IP);
                VCI_SetReference(DeviceType,DeviceInd,CANInd,1,(PVOID) &PORT);
                VCI_SetReference(DeviceType,DeviceInd,CANInd,4,(PVOID) &CANMode);
            }
            else
            {
                VCI_SetReference(DeviceType,DeviceInd,CANInd,2,(PVOID) &PORT);
                VCI_SetReference(DeviceType,DeviceInd,CANInd,4,(PVOID) &CANMode);
            }

        }
            break;
        case (VCI_USBCAN1 || VCI_USBCAN2):
        {
            //0为正常模式，1为只读模式
            VCI_INIT_CONFIG vic;
            VCI_SetReference(DeviceType,DeviceInd,CANInd,0,(PVOID) BAUT);
            vic.Mode = CANMode;
            Status = VCI_InitCAN(DeviceType,DeviceInd,CANInd,&vic);
            if(Status == STATUS_ERR)
            {
                //发送错误信号
                return 0;
            }
        }
            break;
        default:
            break;
        }
        Status = VCI_StartCAN(DeviceType,DeviceInd,CANInd);
        if(Status == 0)
        {
            //发送连接失败信号
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        //打开失败信号
        return 0;
    }
}

void WorkThread::run()
{
    //判断设备类型以及设备工作模式
    DWORD Num;
    while(ThStart)
    {
        //初始化接收缓冲区
        VCI_CAN_OBJ ReceiveBuf[BUFLEN];     //BUFLEN由信号处理更改缓冲区的长度
        memset(ReceiveBuf,0,sizeof(ReceiveBuf));
        Num = VCI_Receive(DeviceType,DeviceInd,CANInd,ReceiveBuf,BUFLEN,-1);
        if(Num > 0)
        {
            QStringList StrList;    //最终接收后的结果表
            char FormatData[3];
            for(DWORD i = 0;i < Num;i++)
            {
                QString Str;     //单行格式化后的字符串
                for(int j = 0;j < ReceiveBuf[i].DataLen;j++)
                {
                    memset(FormatData,0,sizeof(FormatData));
                    sprintf(FormatData,"%02x",ReceiveBuf[i].Data[j]);
                    if(j != ReceiveBuf[i].DataLen - 1)
                    {
                        Str.append(FormatData);
                        Str += ' ';
                    }
                    else
                        Str.append(FormatData);
                }
                StrList.append(Str);
            }
            emit EMITreadFrameSIG(StrList);    //从缓冲区读出的结果以信号参数形式发送
        }
        else continue;
    }
}


void WorkThread::sendFrameSLOT(QString SendDataStr)
{

    VCI_CAN_OBJ vco;
//    vco.RemoteFlag = RemoteFlag;
//    vco.ExternFlag = ExternFlag;
//    vco.SendType = SendType;
//    vco.ID = ID;
    int i = 0,j = 0,CANObjcount = 0;
    while(SendDataStr[i] == ' ')
    {
        i++;
    }
    j = i;
    while(j < SendDataStr.length() && CANObjcount < 8)
    {
        j++;
        if(SendDataStr[j] == ' ')
        {
            QString TempStr;     //中间变量字符串
            if(j - i == 1)
            {
                TempStr.append('0');
            }
            TempStr += SendDataStr.mid(i,j - i);
            vco.Data[CANObjcount++] = TempStr.toInt(nullptr,16);
            while(SendDataStr[j] == ' ')
            {
                j++;
            }
            i = j;
        }
        else if(j - i == 2)
        {
            QString TempStr = SendDataStr.mid(i,j - i);
            vco.Data[CANObjcount++] = TempStr.toInt(nullptr,16);
            i = j;
        }
    }
    vco.DataLen = CANObjcount;
    DWORD SendRes = VCI_Transmit(DeviceType,DeviceInd,CANInd,&vco,1);
    if(SendRes > 0)
    {
        QString TestStr;
        TestStr.append("发送成功: ");
        char FormatData[3];
        for(int i = 0;i < CANObjcount;i++)
        {
            memset(FormatData,0,sizeof(FormatData));
            sprintf(FormatData,"%02x",vco.Data[i]);
            TestStr.append(FormatData);
            TestStr += ' ';
        }
        QStringList StrList;
        StrList.append(TestStr);
        emit EMITreadFrameSIG(StrList);

    }
    else
    {
        QStringList StrList;
        StrList.append(QString("发送失败"));
        emit EMITreadFrameSIG(StrList);
    }
}

void WorkThread::receiveRefrenceSLOT(QString,DWORD)
{

}

WorkThread::~WorkThread()
{}
