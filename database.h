#ifndef DATABASE_H
#define DATABASE_H

#include <QTableWidget>
#include <QObject>
#include <QAbstractItemModel>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"
#define TABLET "film"
#define COLUMN_2 "Название фильма"
#define COLUMN_3 "Описание фильма"

#define NUM_DATA_FOR_CONNECT_TO_DB 5

enum fieldsForConnect {
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

enum requestType {

    requestAllFilms = 1,
    requestComedy   = 2,
    requestHorrors  = 3

};

class DataBase : public QObject {

    Q_OBJECT

public:

    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    void DisconnectFromDataBase(QString nameDb = "");
    void RequestToDB(uint request);
    QSqlError GetLastError(void);
    void ConnectToDataBase(QVector<QString> dataForConnect);

signals:

    void sig_SendDataFromDB(QAbstractItemModel* model, uint typeRequest);
    void sig_SendStatusConnection(bool);

private:

    QString select_comedy = "SELECT * "
                            "FROM film f "
                            "JOIN film_category fc on f.film_id = fc.film_id "
                            "JOIN category c on c.category_id = fc.category_id "
                            "WHERE c.name = 'Comedy'";
    QString select_horror = "SELECT * "
                            "FROM film f "
                            "JOIN film_category fc on f.film_id = fc.film_id "
                            "JOIN category c on c.category_id = fc.category_id "
                            "WHERE c.name = 'Horror'";

    QSqlDatabase* dataBase;
    QSqlTableModel* sqlTableModel;
    QSqlQueryModel* sqlQueryModel;
};

#endif // DATABASE_H
