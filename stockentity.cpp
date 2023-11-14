#include "stockentity.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>

stockentity::stockentity() {}

stockentity::stockentity(const QString &nom, const QString &reference, int quantity, float prixUnitaire)
    : nom(nom), reference(reference), quantity(quantity), prixUnitaire(prixUnitaire) {}

bool stockentity::ajouter()
{
    Connection c;
    //  bool test=c.createconnect();
    QSqlQuery query;
    QString prix=QString::number(prixUnitaire);

    query.prepare("INSERT INTO STOCK(NOM, REFERENCE, QUANTITY, PRIX_UNITAIRE) VALUES (:NOM, :REFERENCE, :QUANTITY, :PRIX_UNITAIRE);");

    query.bindValue(":NOM", nom);
    query.bindValue(":REFERENCE", reference);
    query.bindValue(":QUANTITY", quantity);
    query.bindValue(":PRIX_UNITAIRE", prix);
    qInfo()<<"prixun: "<<prixUnitaire;
    return query.exec();
}

int stockentity::supprimer(QString id)
{


    QSqlQueryModel model;
    QSqlQuery query;
    model.setQuery("SELECT * FROM STOCK WHERE (REFERENCE LIKE '" + id + "');");
    QString Id = model.data(model.index(0, 0)).toString();

    if (Id == "")
        return 2;
    else
    {
        query.prepare("DELETE FROM STOCK WHERE REFERENCE = :id;");
        query.bindValue(":id", id);

        return query.exec();
    }
}

QSqlQueryModel *stockentity::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM STOCK");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITY"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_UNITAIRE"));

    return model;
}

QSqlQueryModel *stockentity::rechercher(const QString &aux)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM STOCK WHERE ((NOM || REFERENCE || QUANTITY || PRIX_UNITAIRE) LIKE '%" + aux + "%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITY"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_UNITAIRE"));

    return model;
}



QSqlQueryModel* stockentity::tri (const QString &aux)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from STOCK order by "+aux+" desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFERENCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITY"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX_UNITAIRE"));

    return model;
}

stockentity stockentity::modifier(QString reference)
{
    stockentity S;
    QSqlQueryModel model;
    QSqlQuery query;

    model.setQuery("SELECT * FROM STOCK WHERE (REFERENCE LIKE '" + reference + "')");

    QString Nom = model.data(model.index(0, 1)).toString();
    QString Reference = model.data(model.index(0, 0)).toString();
    int Quantity = model.data(model.index(0, 2)).toInt();
    float Prix_Unitaire = model.data(model.index(0, 3)).toFloat();

    S.setNom(Nom);
    S.setReference(Reference);
    S.setQuantity(Quantity);
    S.setPrixUnitaire(Prix_Unitaire);

    return S;
}

bool stockentity::modifier2(QString reference, stockentity S)
{
    QSqlQuery query;

    query.prepare("UPDATE STOCK SET NOM = :nom, REFERENCE = :reference, QUANTITY = :quantity, PRIX_UNITAIRE = :prixUnitaire WHERE REFERENCE = :ref;");
    query.bindValue(":ref", reference);
    query.bindValue(":nom", S.getNom());
    query.bindValue(":reference", S.getReference());
    query.bindValue(":quantity", S.getQuantity());
    query.bindValue(":prixUnitaire", S.getPrixUnitaire());

    return query.exec();
}
