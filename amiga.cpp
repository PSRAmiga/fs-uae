#include "amiga.h"
#include "ui_amiga.h"
#include <QFileDialog>
#include <QColorDialog>
#include <QPlastiqueStyle> /////funziona???


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




void Amiga::on_loadKickstartDirButt_clicked()
{
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks); show anly dir
    QString fileName=QFileDialog::getOpenFileName(this, tr("open file"), "/", tr("Image adf/rom(*.adf *.rom)")); //
    ui->kickstartDir->setText(fileName);

}


 // PER CAMBIARE COLORE AL BOTTONE
void Amiga::on_pushButton_17_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    ui->pushButton_17->setText(color.name());
    ui->pushButton_17->setStyleSheet(QString("background-color: ")+color.name());

}

