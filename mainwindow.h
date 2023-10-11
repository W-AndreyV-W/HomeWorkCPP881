#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>


#include "database.h"
#include "dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void ScreenDataFromDB(QAbstractItemModel* model, uint typeRequest);
    void ReceiveStatusConnectionToDB(bool status);

private slots:

    void on_act_addData_triggered();
    void on_act_connect_triggered();
    void on_pb_request_clicked();
    void on_pb_clear_clicked();

signals:

    void sig_RequestToDb(QString request);

private:

    QVector<QString> dataForConnect;

    Ui::MainWindow* ui;
    Dialog* dataDb;
    DataBase* dataBase;
    QMessageBox* msg;
};
#endif // MAINWINDOW_H
