#ifndef STOCK_H
#define STOCK_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
namespace Ui {
class stock;
}

class stock : public QDialog
{
    Q_OBJECT

public:
    explicit stock(QWidget *parent = nullptr);
    ~stock();

private slots:
    void on_ajouter_clicked();



    void on_supprimer_clicked();

    void on_modifier_clicked();

    void on_tabWidget_currentChanged(int index);



    void on_tabWidget_tabBarClicked(int index);



    void on_lineEdit_reference_2_textChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_recherche_textChanged(const QString &arg1);

    void on_pdf_clicked();

    void on_SMS_clicked();

     void replyFinished(QNetworkReply* reply);
private:
    Ui::stock *ui;
};

#endif // STOCK_H
