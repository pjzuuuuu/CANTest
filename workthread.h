#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QThread>

#include "ControlCAN.h"


class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread(QObject* parent = 0);
    ~WorkThread();

protected:
    void run();
private:        //私有方法
    int StartCan();
private:        //私有变量
    bool  ThStart;
    DWORD CANMode;
    DWORD DeviceType;
    DWORD DeviceInd;
    DWORD CANInd;
    char IP[30];
    DWORD PORT;
    DWORD BAUT;
    DWORD BUFLEN;
signals:
    void EMITreadFrameSIG(QStringList);

private slots:
    void sendFrameSLOT(QString);
    void receiveRefrenceSLOT(QString,DWORD);
};

#endif // WORKTHREAD_H
