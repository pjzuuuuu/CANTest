#include "cantestmmainwindow.h"
#include "ui_cantestmmainwindow.h"

CANTestmMainWindow::CANTestmMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CANTestmMainWindow)
{
    ui->setupUi(this);
    connect(ui->actionDevice,SIGNAL(triggered(bool)),this,SLOT(CreatDialog()));
}


void CANTestmMainWindow::CreatDialog()
{
    TCPdlg = new CAN_TCPdlg(this);
    TCPdlg->setModal(false);
    TCPdlg->show();
}

CANTestmMainWindow::~CANTestmMainWindow()
{
    delete ui;
}
