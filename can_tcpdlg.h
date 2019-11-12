#ifndef CAN_TCPDLG_H
#define CAN_TCPDLG_H

#include <QDialog>

namespace Ui {
class CAN_TCPdlg;
}

class CAN_TCPdlg : public QDialog
{
    Q_OBJECT

public:
    explicit CAN_TCPdlg(QWidget *parent = 0);
    ~CAN_TCPdlg();

private:
    Ui::CAN_TCPdlg *ui;
};

#endif // CAN_TCPDLG_H
