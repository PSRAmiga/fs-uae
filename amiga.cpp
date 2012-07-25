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
    ui->setupUi(this);
}

Amiga::~Amiga()
{
    delete ui;
}


void Amiga::on_kickstartFileToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Image adf/rom(*.adf *.rom)"));
    ui->kickstartFileLineEdit->setText(fileName);
    configChipset.setParameter("kickstart_file",fileName.toStdString());
}

void Amiga::on_kickstartExtFileToolButton_clicked()
{
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Image ROM(*.rom)"));
    ui->kickstartExtFileLineEdit->setText(fileName);
    configChipset.setParameter("kickstart_ext_file",fileName.toStdString());
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
    this->configChipset.setParameter("accuracy","-1");
}

void Amiga::on_accuracyNormalRadio_clicked()
{
    this->configChipset.setParameter("accuracy","0");
}

void Amiga::on_accuracyMostadio_clicked()
{
    this->configChipset.setParameter("accuracy","1");
}

void Amiga::on_saveConfigToolButton_clicked()
{
    //ui->kickstartExtFileLineEdit->setText(QString::fromStdString(configChipset.getAccuracyString()));
    QString fileName=QFileDialog::getSaveFileName(this, tr("Save file as"), "/", tr("Config file *.fs-uae (*.fs-uae)"));


    //fare check sull'estensione
    string fileNameString;

    if(fileName.contains(".fs-uae", Qt::CaseInsensitive)) {fileNameString=fileName.toStdString();}
    else {fileNameString=fileName.toStdString()+".fs-uae";}


    //TODO devo controllare gli errore sulla scrittura/lettura /////////////////////////////////////////////////////////////////////////////////

    ofstream myfile;
    //myfile.open ("/home/davide/Desktop/prova.txt",ios::out);
    myfile.open(fileNameString.c_str(),ios::out);

    myfile << configChipset.getAccuracyConfigString() << endl;
    myfile << configChipset.getNTSCModeConfigString() << endl;
    myfile.close();
}


void Amiga::parseLine(string line){
    if (line.length()==0) return;
    //fs-uae config file convention is "name = value"
    int separatorPosition=line.find_last_of(" = ");
    string parameterName=line.substr(0,separatorPosition-2);
    string parameterValue=line.substr(separatorPosition+1,line.length()-1);

    //bisogna capire in quale configurazione indirizzarlo, poi ogni config si sistema da sola internamente
    //magari con una funzione del tipo getConfigurationAreaFromParameterName(parameterName) che restituisce
    //una string oppure una ENUM

    configChipset.setParameter(parameterName,parameterValue);

}

void Amiga::updateGraphicsFromInternalConfiguration(){
    //ACCURACY
    string accuracy=this->configChipset.getAccuracyString();
    if (accuracy.compare("-1")==0){
        ui->accuracyLeastRadio->setChecked(true);
    } else if (accuracy.compare("0")==0){
        ui->accuracyNormalRadio->setChecked(true);
    } else {
        ui->accuracyMostadio->setChecked(true);
    }

    //NTSC MODE
   string ntsc_mode=this->configChipset.getNTSCModeString();
   if (ntsc_mode.compare("0")==0){
       ui->videoModePALRadio->setChecked(true);
   } else if (ntsc_mode.compare("1")==0){
       ui->videoModeNTSCRadio->setChecked(true);
   }

}

void Amiga::on_loadConfigToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Config file *.fs-uae (*.fs-uae)"));

    //devo resettare tutte le impostazioni a default perchè nel file i valori di defult non sono esplicitamente salvati
    //quindi rischierei di vedere i valori dell'ultima config

    configChipset.setToDefaultConfiguration();

    //poi leggo riga per riga, aggiorno la configurazione interna e aggiorno i componenti

    string line;
    ifstream myfile(fileName.toStdString().c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            getline (myfile,line);
            parseLine(line);
        }
        myfile.close();
    }

    //lo devo fare per ogni configuration area
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_videoModePALRadio_clicked()
{
    this->configChipset.setParameter("ntsc_mode","0");
}

void Amiga::on_videoModeNTSCRadio_clicked()
{
    this->configChipset.setParameter("ntsc_mode","1");
}
