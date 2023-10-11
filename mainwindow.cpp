#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);

    dataDb = new Dialog(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);

    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    QObject::connect(dataDb, &Dialog::sig_sendData, this, [&] (QVector<QString> receivData) {

        dataForConnect = receivData;
    });
    QObject::connect(dataBase, &DataBase::sig_SendDataFromDB, this, &MainWindow::ScreenDataFromDB);
    QObject::connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);
}

MainWindow::~MainWindow() {

    delete ui;
}

void MainWindow::on_act_addData_triggered() {

    dataDb->show();
}

void MainWindow::on_act_connect_triggered() {

    if(ui->lb_statusConnect->text() == "Отключено") {

        ui->lb_statusConnect->setText("Подключение");
        ui->lb_statusConnect->setStyleSheet("color : black");

        auto conn = [&] () {

            dataBase->ConnectToDataBase(dataForConnect);
        };

        auto fun = QtConcurrent::run(conn);
    }
    else {

        dataBase->DisconnectFromDataBase(DB_NAME);

        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);
    }
}

void MainWindow::on_pb_request_clicked() {

    uint request = 0;
    QString type = ui->cb_category->currentText();

    if (type == "Все") {

        request = requestAllFilms;
    }
    else if (type == "Комедия") {

        request = requestComedy;
    }
    else if (type == "Ужасы") {

        request = requestHorrors;
    }

    dataBase->RequestToDB(request);
}

void MainWindow::ScreenDataFromDB(QAbstractItemModel* model, uint num_column) {

    model->setHeaderData(1, Qt::Horizontal, tr(COLUMN_2));
    model->setHeaderData(2, Qt::Horizontal, tr(COLUMN_3));

    ui->tb_result->setModel(model);
    ui->tb_result->hideColumn(0);

    for(uint i = 3; i < num_column; i++) {

        ui->tb_result->hideColumn(i);
    }

}

void MainWindow::ReceiveStatusConnectionToDB(bool status) {

    if(status) {

        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        ui->pb_request->setEnabled(true);
    }
    else {

        dataBase->DisconnectFromDataBase(DB_NAME);

        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());

        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");

        msg->exec();
    }
}

void MainWindow::on_pb_clear_clicked() {

    ui->tb_result->setModel(nullptr);
}

