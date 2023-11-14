#ifndef STOCKENTITY_H
#define STOCKENTITY_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>



class stockentity
{
public:
    stockentity();
    stockentity(const QString &nom, const QString &reference, int quantity, float prixUnitaire);

    QString getNom() const { return nom; }
     QString getReference() const { return reference; }
     int getQuantity() const { return quantity; }
     float getPrixUnitaire() const { return prixUnitaire; }

     // Setters
     void setNom(const QString &nom) { this->nom = nom; }
     void setReference(const QString &reference) { this->reference = reference; }
     void setQuantity(int quantity) { this->quantity = quantity; }
     void setPrixUnitaire(float prixUnitaire) { this->prixUnitaire = prixUnitaire; }


    bool ajouter();
       QSqlQueryModel * afficher();
       QSqlQueryModel * rechercher(const QString &aux);
        QSqlQueryModel * tri(const QString &aux);
       int supprimer(QString);
       stockentity modifier(QString);
       bool modifier2(QString,stockentity);

private:
    QString nom;
    QString reference;
    int quantity;
    float prixUnitaire;
};

#endif // STOCKENTITY_H
