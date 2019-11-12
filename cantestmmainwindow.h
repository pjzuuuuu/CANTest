#ifndef CANTESTMMAINWINDOW_H
#define CANTESTMMAINWINDOW_H

#include <QMainWindow>
#include "can_tcpdlg.h"

namespace Ui {
class CANTestmMainWindow;
}

class CANTestmMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CANTestmMainWindow(QWidget *parent = 0);
    ~CANTestmMainWindow();

protected:


private:
    CAN_TCPdlg* TCPdlg;

private:
    Ui::CANTestmMainWindow *ui;


signals:

private slots:
    void CreatDialog();
};

#endif // CANTESTMMAINWINDOW_H
