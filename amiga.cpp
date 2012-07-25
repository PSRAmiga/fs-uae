#include "amiga.h"
#include "ui_amiga.h"
#include <fstream>
#include <QFileDialog>
#include <QColorDialog>
using namespace std;


Amiga::Amiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amiga)
{
    //creates standard configurations

    ui->setupUi(this);


}

Amiga::~Amiga()
{
    delete ui;
}




void Amiga::on_kickstartFileToolButton_clicked()
{

    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Image adf/rom(*.adf *.rom)")); //
    ui->kickstartFileLineEdit->setText(fileName);

}

void Amiga::on_kickstartExtFileToolButton_clicked()
{
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Image ROM(*.rom)")); //
    ui->kickstartExtFileLineEdit->setText(fileName);
}

 // PER CAMBIARE COLORE AL BOTTONE
void Amiga::on_pushButton_17_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    ui->pushButton_17->setText(color.name());
    ui->pushButton_17->setStyleSheet(QString("background-color: ")+color.name());

}



void Amiga::on_amigaModelComboBox_currentIndexChanged(const QString &arg1)
{
    //Enable or Disable Kickstart extend Dir selection
    if ((QString::compare(arg1,"CD32")==0)||(QString::compare(arg1,"CDTV")==0))
    {
        ui->kickstartExtFileLabel->setEnabled(true);
        ui->kickstartExtFileLineEdit->setEnabled(true);
        ui->kickstartExtFileToolButton->setEnabled(true);
    } else
    {
        ui->kickstartExtFileLabel->setEnabled(false);
        ui->kickstartExtFileLineEdit->setEnabled(false);
        ui->kickstartExtFileToolButton->setEnabled(false);
    }

}

void Amiga::on_accuracyLeastRadio_clicked()
{
    this->configChipset.setAccuracy(ui->accuracyLeastRadio->isChecked(),ui->accuracyNormalRadio->isChecked(),ui->accuracyMostadio->isChecked());
}

void Amiga::on_accuracyNormalRadio_clicked()
{
    this->configChipset.setAccuracy(ui->accuracyLeastRadio->isChecked(),ui->accuracyNormalRadio->isChecked(),ui->accuracyMostadio->isChecked());
}

void Amiga::on_accuracyMostadio_clicked()
{
    this->configChipset.setAccuracy(ui->accuracyLeastRadio->isChecked(),ui->accuracyNormalRadio->isChecked(),ui->accuracyMostadio->isChecked());
}

void Amiga::on_saveConfigToolButton_clicked()
{
 ui->kickstartExtFileLineEdit->setText(QString::fromStdString(configChipset.getAccuracyString()));
 QString fileName=QFileDialog::getSaveFileName(this, tr("Save file as"), "/", tr("Config file(*.fs-uae)"));


 //fare check sull'estensione
 string fileNameString;
 if(fileName.toStdString().find(".fs-uae")!=fileName.toStdString().length()-7) {fileNameString=fileName.toStdString()+".fs-uae";}
 else {fileNameString=fileName.toStdString();}

 ofstream myfile;
 //myfile.open ("/home/davide/Desktop/prova.txt",ios::out);
 myfile.open(fileNameString.c_str(),ios::out);

 myfile << this->configChipset.getAccuracyString() << endl;
 myfile.close();
}
