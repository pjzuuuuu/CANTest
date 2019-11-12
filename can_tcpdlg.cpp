#include "can_tcpdlg.h"
#include "ui_can_tcpdlg.h"

CAN_TCPdlg::CAN_TCPdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAN_TCPdlg)
{
    ui->setupUi(this);
}

CAN_TCPdlg::~CAN_TCPdlg()
{
    delete ui;
}
