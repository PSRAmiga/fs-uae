#include "amiga.h"
#include "ui_amiga.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QPlastiqueStyle> //funziona??


Amiga::Amiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amiga)
{
    ui->setupUi(this);
}

Amiga::~Amiga()
{
    delete ui;
}




void Amiga::on_kickstartFileToolButton_clicked()
{

    QString fileName=QFileDialog::getOpenFileName(this, tr("open file"), "/", tr("Image adf/rom(*.adf *.rom)")); //
    ui->kickstartFileLineEdit->setText(fileName);

}

void Amiga::on_kickstartExtFileToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->kickstartExtFileLineEdit->setText(dir);
}

 // PER CAMBIARE COLORE AL BOTTONE
void Amiga::on_fadeColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    ui->fadeColorPushButton->setText(color.name());
    ui->fadeColorPushButton->setStyleSheet(QString("background-color: ")+color.name());

}
