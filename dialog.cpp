#include "dialog.h"
#include "database.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDB)
{

    ui->setupUi(this);

    ui->lE_HostName->setText("981757-ca08998.tmweb.ru");
    ui->lE_NameDB->setText("netology_cpp");
    ui->lE_Login->setText("netology_usr_cpp");
    ui->lE_Password->setText("CppNeto3");
    ui->sB_DBConnectionPort->setValue(5432);

    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
}

Dialog::~Dialog()
{

    delete ui;
}

void Dialog::on_buttonBox_accepted() {

    data[hostName] = ui->lE_HostName->text();
    data[dbName] = ui->lE_NameDB->text();
    data[login] = ui->lE_Login->text();
    data[pass] = ui->lE_Password->text();
    data[port] = ui->sB_DBConnectionPort->text();

    emit sig_sendData(data);
}

