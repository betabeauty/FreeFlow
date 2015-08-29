#include "selection.h"
#include "ui_selection.h"
#include <QDebug>
#include <QString>

Selection::Selection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selection)
{
    ui->setupUi(this);
}

Selection::~Selection()
{

    delete ui;
}

void Selection::accept()
{
    QString si = ui->size->currentText();
    si = si[0];
    //qDebug()<< si;
    QString le = ui->level->currentText();
    //qDebug() << le;
    if (le == "ONE")
        le = "1";
    else if(le == "TWO")
        le = "2";
    else if(le == "THREE")
        le = "3";
    else
        le = "ERROR";
    bool ok;
    size = si.toInt(&ok,10);
    level = le.toInt(&ok, 10);

    emit getChoice(size, level);
    QDialog::accept();
}

void Selection::on_buttonBox_accepted()
{

}
