#include "stock.h"
#include "ui_stock.h"
#include "connection.h"
#include "stockentity.h"
#include <QMessageBox>

#include <QFileDialog>
#include<QPdfWriter>
#include<QPainter>
#include <QPrinter>
#include <QDate>



stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);


}

stock::~stock()
{
    delete ui;
}

void stock::on_ajouter_clicked()
{
    stockentity S;
    ui->tableView->setModel(S.afficher());

    if (!ui->lineEdit_reference->text().isEmpty()) {
        QString nom = ui->lineEdit_nom->text();
        QString reference = ui->lineEdit_reference->text();
        int quantity = ui->spinBox_quantity->value();
        float prixUnitaire = ui->doubleSpinBox_prixUnitaire->value();

        S.setNom(nom);
        S.setReference(reference);
        S.setQuantity(quantity);
        S.setPrixUnitaire(prixUnitaire);

        bool test = S.ajouter();

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                QObject::tr("Ajout non effectué.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("Please don't leave Reference empty.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}





void stock::on_supprimer_clicked()
{  stockentity S;
    if (!ui->lineEdit_reference_2->text().isEmpty()) {
        QString reference = ui->lineEdit_reference_2->text();
        int test = S.supprimer(reference);

        if (test == 1) {
            ui->tableView->setModel(S.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Suppression effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
            // Additional logic if needed after successful deletion

        } else if (test == 2) {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                QObject::tr("Reference n'existe pas.\nClick Cancel to exit."), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                QObject::tr("Suppression non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("Please don't leave Reference empty.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}


void stock::on_modifier_clicked()
{stockentity S;
    if (!ui->lineEdit_reference_2->text().isEmpty()) {
        QString reference = ui->lineEdit_reference_2->text();
        S = S.modifier(reference);

        if (!S.getReference().isEmpty()) {
            // Modify the stock entity attributes as needed based on your UI elements
            QString nom = ui->lineEdit_nom->text();
            int quantity = ui->spinBox_quantity->value();
            float prixUnitaire = ui->doubleSpinBox_prixUnitaire->value();

            S.setNom(nom);
            S.setQuantity(quantity);
            S.setPrixUnitaire(prixUnitaire);

            bool test = S.modifier2(reference, S);

            if (test) {
                ui->tableView->setModel(S.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
            } else {
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Modification non effectuée.\nClick Cancel to exit."), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                QObject::tr("Reference n'existe pas.\nClick Cancel to exit."), QMessageBox::Cancel);
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("Please don't leave Reference empty.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

}


void stock::on_tabWidget_currentChanged(int index)
{
    stockentity S;
    ui->tableView->setModel(S.afficher());
}




void stock::on_tabWidget_tabBarClicked(int index)
{
    stockentity S;
    ui->tableView->setModel(S.afficher());
}


void stock::on_lineEdit_reference_2_textChanged(const QString &arg1)
{
    stockentity S;
    S = S.modifier(ui->lineEdit_reference_2->text());


        // Access the properties of the returned object
        QString nom = S.getNom();
        QString reference = S.getReference();
        int quantity = S.getQuantity();
        float prixUnitaire = S.getPrixUnitaire();

        // Update UI elements with the retrieved data
        ui->lineEdit_nom->setText(nom);
        ui->lineEdit_reference->setText(reference);
        ui->spinBox_quantity->setValue(quantity);
        ui->doubleSpinBox_prixUnitaire->setValue(prixUnitaire);


}


void stock::on_comboBox_activated(const QString &arg1)
{
    stockentity S;
   QString type=ui->comboBox->currentText();
      ui->tableView->setModel(S.tri(type));
}


void stock::on_recherche_textChanged(const QString &arg1)
{stockentity S;
    QString rech= ui->recherche->text();
       ui->tableView->setModel(S.rechercher(rech));
}


void stock::on_pdf_clicked()
{
    QPdfWriter pdf("liste.pdf");

        QPainter painter(&pdf);
        int i = 4100;

        // Définir la couleur rouge pour SOS Alarmy
        QColor sosColor(0xFF0000);
        painter.setPen(sosColor);

        painter.setFont(QFont("Montserrat SemiBold", 11));
        QDate cd = QDate::currentDate();
        QDateTime now = QDateTime::currentDateTime();
        painter.drawText(8400,1000,cd.toString("Tunis"));
        /*painter.drawText(8100,1300,cd.toString("dd/MM/yyyy"));*/
        painter.drawText(7700,1300,now.toString("yyyy-MM-dd HH:mm:ss"));
    /*
        // Afficher SOS Alarmy en haut de la page
        painter.setFont(QFont("Montserrat SemiBold", 25));
        painter.drawText(100, 300, "SOS Alarmy");
        */


        // Insérer le logo en dessous de SOS Alarmy
        QImage logo("logo.png");
        if (!logo.isNull()) {
            logo = logo.scaledToHeight(1500, Qt::SmoothTransformation);
            painter.drawImage(QRectF(10, 2, logo.width(), logo.height()), logo);
        }

        QColor titleColor(0x341763);
        painter.setPen(titleColor);
        painter.setFont(QFont("Montserrat SemiBold", 25));

        painter.drawText(3000,2700,"Liste de Stock");

        painter.setPen(QPen(Qt::black, 50));
        painter.drawRect(0, 0, pdf.width(), pdf.height());


        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(100,3300,9400,500);

        painter.setFont(QFont("Montserrat SemiBold", 10));

        painter.drawText(500,3600,"Reference");
        painter.drawText(2000,3600,"Nom");
        painter.drawText(3300,3600,"Quantite");
        painter.drawText(4500,3600,"Prix_Unitaire");

        painter.setFont(QFont("Montserrat", 10));

        QSqlQuery query;
        query.prepare("select * from Stock");
        query.exec();
        int y=4300;
        while (query.next())
        {
            painter.drawLine(100,y,9500,y);
            y+=500;
            painter.drawText(500,i,query.value(0).toString());
            painter.drawText(2000,i,query.value(1).toString());
            painter.drawText(3300,i,query.value(2).toString());
            painter.drawText(4500,i,query.value(3).toString());



            i = i + 500;
        }

        painter.drawLine(100, 3800, 9500, 3800);
        painter.drawLine(100, i, 9500, i);
/*
        // Insérer le cachet en bas de page
        QImage cachet("C:/Users/abdou/OneDrive/Documents/Patient/images/cachet.png");
        if (!cachet.isNull()) {
            cachet = cachet.scaledToWidth(1500, Qt::SmoothTransformation);
            painter.drawImage(QRectF(7500, 11000, cachet.width(), cachet.height()), cachet);
        }
*/
        QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
            QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


void stock::on_SMS_clicked()
{
        QString phonenumber=ui->numero->text();
        QString content=ui->message->toPlainText();
       // qInfo()<<"sms : "<<content;


   qInfo() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    // Twilio Account SID and Auth Token
           QString accountSid = "AC7f53a7e69e2c965619864b19edde338f";
           QString authToken = "4a9cee812f36fca7f50647180bc0c8db"; // Replace with your actual Auth Token

           // Twilio API URL
           QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + accountSid + "/Messages.json");

           // Create a network manager
           QNetworkAccessManager* manager = new QNetworkAccessManager(this);

           // Set up the request
           QNetworkRequest request(url);
           request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

           // Set up authentication
           QString credentials = accountSid + ":" + authToken;
           QByteArray encodedCredentials = credentials.toUtf8().toBase64();
           request.setRawHeader("Authorization", "Basic " + encodedCredentials);

           // Set up the request parameters
           QUrlQuery params;
           params.addQueryItem("From", "+12494872347");
           params.addQueryItem("To", phonenumber); // Replace with your recipient's phone number
           params.addQueryItem("Body", content);
           // Connect signals and slots
           connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

           // Send the POST request
           manager->post(request, params.query().toUtf8());



}



void stock::replyFinished(QNetworkReply* reply)
{
           //QByteArray bts = rep->readAll();


           QByteArray buffer = reply->readAll();
           qDebug() << buffer;
           QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
           QJsonObject jsonReply = jsonDoc.object();

           QJsonObject response = jsonReply["response"].toObject();
           QJsonArray  data     = jsonReply["data"].toArray();
         //  qDebug() << data;
           qDebug() << response;

}


