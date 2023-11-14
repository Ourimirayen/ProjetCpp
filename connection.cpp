#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("Source_Projet2A");
db.setUserName("ourimi");//inserer nom de l'utilisateur
db.setPassword("ourimi");//inserer mot de passe de cet utilisateur

if (!db.open())
{
    qDebug() << "Database error: " << db.lastError().text();
}

if (db.open())
test=true;

    return  test;
}

void Connection::closeconnection(){db.close();}



