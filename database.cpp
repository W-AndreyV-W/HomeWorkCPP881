#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    sqlQueryModel = new QSqlQueryModel(this);
}

DataBase::~DataBase() {

    delete dataBase;
}

void DataBase::AddDataBase(QString driver, QString nameDB) {

    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

void DataBase::ConnectToDataBase(QVector<QString> data) {

    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    bool status = dataBase->open();

    emit sig_SendStatusConnection(status);

    sqlTableModel = new QSqlTableModel(this, *dataBase);
}

void DataBase::DisconnectFromDataBase(QString nameDb) {

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}

void DataBase::RequestToDB(uint request) {

    if (request == requestAllFilms) {

        sqlTableModel->setTable(TABLET);
        sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        sqlTableModel->select();

        emit sig_SendDataFromDB(sqlTableModel, sqlTableModel->record().count());
    }
    else if(request == requestComedy) {

        sqlQueryModel->setQuery(select_comedy, *dataBase);

        emit sig_SendDataFromDB(sqlQueryModel, sqlQueryModel->record().count());
    }
    else if(request == requestHorrors) {

        sqlQueryModel->setQuery(select_horror, *dataBase);

        emit sig_SendDataFromDB(sqlQueryModel, sqlQueryModel->record().count());
    }
}

QSqlError DataBase::GetLastError() {

    return dataBase->lastError();
}
