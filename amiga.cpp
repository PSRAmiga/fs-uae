#include "amiga.h"
#include "ui_amiga.h"
#include <fstream>
#include <QUrl>
#include <QDesktopServices>
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
    chipsetConfiguration.setParameter("kickstart_file",fileName.toStdString());
}

void Amiga::on_kickstartExtFileToolButton_clicked()
{
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Image ROM(*.rom)"));
    ui->kickstartExtFileLineEdit->setText(fileName);
    chipsetConfiguration.setParameter("kickstart_ext_file",fileName.toStdString());
}


// PER CAMBIARE COLORE AL BOTTONE
void Amiga::on_fadeColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    ui->fadeColorPushButton->setText(color.name());
    ui->fadeColorPushButton->setStyleSheet(QString("background-color: ")+color.name());

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

    if ((QString::compare(arg1,"A1200/020")==0)||(QString::compare(arg1,"A4000/040")==0)||(QString::compare(arg1,"CD32")==0))
    {
        ui->slowMem1_8MbRadio->setDisabled(true);
    } else
    {
        ui->slowMem1_8MbRadio->setDisabled(false);
    }

    chipsetConfiguration.setParameter("amiga_model",arg1.toStdString());
}

void Amiga::on_accuracyLeastRadio_clicked()
{
    this->chipsetConfiguration.setParameter("accuracy","-1");
}

void Amiga::on_accuracyNormalRadio_clicked()
{
    this->chipsetConfiguration.setParameter("accuracy","0");
}

void Amiga::on_accuracyMostadio_clicked()
{
    this->chipsetConfiguration.setParameter("accuracy","1");
}

bool isEmptyString(string s){
     //NB compare ritorna 0 se è la comparazione è vera, è il contrario!
    return !(s.compare(""));
}

void Amiga::on_saveConfigToolButton_clicked()
{
    //ui->kickstartExtFileLineEdit->setText(QString::fromStdString(configChipset.getAccuracyString()));
    QString fileName=QFileDialog::getSaveFileName(this, tr("Save file as"), "/", tr("Config file *.fs-uae (*.fs-uae)"));
    if (fileName.compare("")==0) {return; }

    //fare check sull'estensione
    string fileNameString;

    if(fileName.contains(".fs-uae", Qt::CaseInsensitive)) {fileNameString=fileName.toStdString();}
    else {fileNameString=fileName.toStdString()+".fs-uae";}


    //TODO devo controllare gli errore sulla scrittura/lettura /////////////////////////////////////////////////////////////////////////////////

    ofstream myfile;
    //myfile.open ("/home/davide/Desktop/prova.txt",ios::out);
    myfile.open(fileNameString.c_str(),ios::out);

    myfile << "[config]" <<endl;



    if (!isEmptyString(chipsetConfiguration.getAccuracyConfigString())) {myfile << chipsetConfiguration.getAccuracyConfigString() << endl;}
    if (!isEmptyString(chipsetConfiguration.getNTSCModeConfigString())) {myfile << chipsetConfiguration.getNTSCModeConfigString() << endl;}
    if (!isEmptyString(chipsetConfiguration.getAmigaModelConfigString())) {myfile << chipsetConfiguration.getAmigaModelConfigString() << endl;}
    if (!isEmptyString(chipsetConfiguration.getKickstartFileConfigString())) {myfile << chipsetConfiguration.getKickstartFileConfigString() << endl;}
    if (!isEmptyString(chipsetConfiguration.getKickstartExtFileConfigString())) {myfile << chipsetConfiguration.getKickstartExtFileConfigString() << endl;}

    if (!isEmptyString(ramConfiguration.getChipMemoryConfigString())) {myfile << ramConfiguration.getChipMemoryConfigString() << endl;}
    if (!isEmptyString(ramConfiguration.getFastMemoryConfigString())) {myfile << ramConfiguration.getFastMemoryConfigString() << endl;}
    if (!isEmptyString(ramConfiguration.getSlowMemoryConfigString())) {myfile << ramConfiguration.getSlowMemoryConfigString() << endl;}
    if (!isEmptyString(ramConfiguration.getZorro3ConfigString())) {myfile << ramConfiguration.getZorro3ConfigString() << endl;}

    myfile.close();
}

int Amiga::getConfigurationAreaFromParameterName(string parameterName){
    //per ora ritorno un numero/una stringa poi magari potrei fare una configurazione astratta e ritornare direttamente l'oggetto chipsetConfiguration.
    //ovviamente tutte le config dovranno implemntare l'astratta così questa funzione ritorna un oggetto di tipo padre abstract config
    //e posso fare abstrobj.setParameter(...) con un'unica riga dentro a parseLine()


    if ((parameterName.compare("amiga_model")==0)||(parameterName.compare("accuracy")==0)||(parameterName.compare("kickstart_file")==0)||(parameterName.compare("kickstart_ext_file")==0)||(parameterName.compare("ntsc_mode")==0)) {
        return 1;
    } else if ((parameterName.compare("chip_memory")==0)||(parameterName.compare("slow_memory")==0)||(parameterName.compare("fast_memory")==0)||(parameterName.compare("zorro_iii_memory")==0)){
        return 2;
    } else {
        return -1;
    }
}

void Amiga::parseLine(string line){
    if (line.length()==0) return;
    //fs-uae config file convention is "name = value"

    int separatorPosition=line.find_first_of(" = ");
    string parameterName=line.substr(0,separatorPosition);
    string parameterValue=line.substr(separatorPosition+3,line.length()-1);

    //bisogna capire in quale configurazione indirizzarlo, poi ogni config si sistema da sola internamente
    //magari con una funzione del tipo getConfigurationAreaFromParameterName(parameterName) che restituisce
    //una string oppure una ENUM
    int configArea=getConfigurationAreaFromParameterName(parameterName);
    if (configArea==1){
        chipsetConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==2){
        ramConfiguration.setParameter(parameterName,parameterValue);
    }


}

void Amiga::updateGraphicsFromInternalConfiguration(){
    //ACCURACY
    string accuracy=this->chipsetConfiguration.getAccuracyString();
    if (accuracy.compare("-1")==0){
        ui->accuracyLeastRadio->setChecked(true);
    } else if (accuracy.compare("0")==0){
        ui->accuracyNormalRadio->setChecked(true);
    } else {
        ui->accuracyMostadio->setChecked(true);
    }

    //NTSC MODE
    string ntsc_mode=this->chipsetConfiguration.getNTSCModeString();
    if (ntsc_mode.compare("1")==0){
        ui->videoModeNTSCRadio->setChecked(true);
    } else {
        ui->videoModePALRadio->setChecked(true);
    }

    //AMIGA MODEL
    string amiga_model=this->chipsetConfiguration.getAmigaModelString();
    if(ui->amigaModelComboBox->findText(QString::fromStdString(amiga_model),Qt::MatchExactly)!=-1){
        ui->amigaModelComboBox->setCurrentIndex(ui->amigaModelComboBox->findText(QString::fromStdString(amiga_model),Qt::MatchExactly));
    } else {ui->amigaModelComboBox->setCurrentIndex(0); }

    if ((amiga_model.compare("CD32")==0)||(amiga_model.compare("CDTV")==0))
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

    //KICKSTART ROM
    string kickstart_file=this->chipsetConfiguration.getKickstartFileString();
    ui->kickstartFileLineEdit->setText(QString::fromStdString(kickstart_file));

    //KICKSTART EXT ROM
    string kickstart_ext_file=this->chipsetConfiguration.getKickstartExtFileString();
    ui->kickstartExtFileLineEdit->setText(QString::fromStdString(kickstart_ext_file));

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //CHIP MEMORY
    string chip_memory=this->ramConfiguration.getChipMemoryString();
    if (chip_memory.compare("8192")==0){
        ui->chipMeme8MbRadio->setChecked(true);
    } else if (chip_memory.compare("4096")==0){
        ui->chipMem4MbRadio->setChecked(true);
    } else if (chip_memory.compare("2048")==0){
        ui->chipMem2MbRadio->setChecked(true);
    } else if (chip_memory.compare("1024")==0){
        ui->chipMem1MbRadio->setChecked(true);
    } else {
        ui->chipMem512KbRadio->setChecked(true);
    }

    //SLOW MEMORY
    string slow_memory=this->ramConfiguration.getSlowMemoryString();
    if (slow_memory.compare("1792")==0){
        ui->slowMem1_8MbRadio->setChecked(true);
    } else if (slow_memory.compare("1024")==0){
        ui->slowMem1MbRadio->setChecked(true);
    } else if (slow_memory.compare("512")==0){
        ui->slowMem512KbRadio->setChecked(true);
    } else {
        ui->slowMemNoneRadio->setChecked(true);
    }

    //FAST MEMORY
    string fast_memory=this->ramConfiguration.getFastMemoryString();
    if (fast_memory.compare("8192")==0){
        ui->fastMem8MbRadio->setChecked(true);
    } else if (fast_memory.compare("4096")==0){
        ui->fastMem4MbRadio->setChecked(true);
    } else if (fast_memory.compare("2048")==0){
        ui->fastMem2MbRadio->setChecked(true);
    } else if (fast_memory.compare("1024")==0){
        ui->fastMem1MbRadio->setChecked(true);
    } else {
        ui->fastMemNoneRadio->setChecked(true);
    }

    string zorro_iii_memory=this->ramConfiguration.getZorro3String();
    if (zorro_iii_memory.compare("262144")==0){
        ui->z3Mem256MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("131072")==0){
        ui->z3Mem128MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("65536")==0){
        ui->z3Mem64MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("32768")==0){
        ui->z3Mem32MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("16384")==0){
        ui->z3Mem16MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("8192")==0){
        ui->z3Mem8MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("4096")==0){
        ui->z3Mem4MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("2048")==0){
        ui->z3Mem2MbRadio->setChecked(true);
    } else if (zorro_iii_memory.compare("1024")==0){
        ui->z3Mem1MbRadio->setChecked(true);
    } else {
        ui->z3MemNoneRadio->setChecked(true);
    }

}

void Amiga::on_loadConfigToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), "/", tr("Config file *.fs-uae (*.fs-uae)"));
    if (fileName.compare("")==0) {return; }

    //devo resettare tutte le impostazioni a default perchè nel file i valori di defult non sono esplicitamente salvati
    //quindi rischierei di vedere i valori dell'ultima config

    chipsetConfiguration.setToDefaultConfiguration();

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
    this->chipsetConfiguration.setParameter("ntsc_mode","0");
}

void Amiga::on_videoModeNTSCRadio_clicked()
{
    this->chipsetConfiguration.setParameter("ntsc_mode","1");
}


void Amiga::on_actionReport_bug_triggered()
{
    QDesktopServices::openUrl(QUrl(tr("mailto:alessandromario.riva@gmail.com,dsanvito90@gmail.com?subject=FS-UAE Gui Bug Report")));
}

void Amiga::on_loadDefaultValuesToolButton_clicked()
{
    chipsetConfiguration.setToDefaultConfiguration();
    ramConfiguration.setToDefaultConfiguration();
    //confiRAM.setToDefaultConfiguration();     //ecc per tutti gli altri
    updateGraphicsFromInternalConfiguration();

    //DEVO DISABILITARE KICK_EXT_DIR e tutte le cose che di default sarebbero disabilitate!

}

void Amiga::setFastMemoryDisabled(bool state){
    ui->fastMem1MbRadio->setDisabled(state);
    ui->fastMem2MbRadio->setDisabled(state);
    ui->fastMem4MbRadio->setDisabled(state);
    ui->fastMem8MbRadio->setDisabled(state);
    ui->fastMemLabel->setDisabled(state);
    ui->fastMemNoneRadio->setDisabled(state);

}

void Amiga::on_chipMem4MbRadio_clicked()
{
    setFastMemoryDisabled(true);
    this->ramConfiguration.setParameter("chip_memory","4096");
}

void Amiga::on_chipMeme8MbRadio_clicked()
{
    setFastMemoryDisabled(true);
    this->ramConfiguration.setParameter("chip_memory","8192");
}

void Amiga::on_chipMem512KbRadio_clicked()
{
    setFastMemoryDisabled(false);
    this->ramConfiguration.setParameter("chip_memory","512");
}

void Amiga::on_chipMem1MbRadio_clicked()
{
    setFastMemoryDisabled(false);
    this->ramConfiguration.setParameter("chip_memory","1024");
}

void Amiga::on_chipMem2MbRadio_clicked()
{
    setFastMemoryDisabled(false);
    this->ramConfiguration.setParameter("chip_memory","2048");
}

void Amiga::on_slowMemNoneRadio_clicked()
{
    this->ramConfiguration.setParameter("slow_memory","NONE");
}

void Amiga::on_slowMem512KbRadio_clicked()
{
    this->ramConfiguration.setParameter("slow_memory","512");
}

void Amiga::on_slowMem1MbRadio_clicked()
{
    this->ramConfiguration.setParameter("slow_memory","1024");
}

void Amiga::on_slowMem1_8MbRadio_clicked()
{
    this->ramConfiguration.setParameter("slow_memory","1792");
}

void Amiga::on_fastMemNoneRadio_clicked()
{
    this->ramConfiguration.setParameter("fast_memory","NONE");
}

void Amiga::on_fastMem1MbRadio_clicked()
{
    this->ramConfiguration.setParameter("fast_memory","1024");
}

void Amiga::on_fastMem2MbRadio_clicked()
{
    this->ramConfiguration.setParameter("fast_memory","2048");
}

void Amiga::on_fastMem4MbRadio_clicked()
{
    this->ramConfiguration.setParameter("fast_memory","4096");
}

void Amiga::on_fastMem8MbRadio_clicked()
{
    this->ramConfiguration.setParameter("fast_memory","8192");
}

void Amiga::on_z3MemNoneRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","NONE");
}

void Amiga::on_z3Mem1MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","1024");
}


void Amiga::on_z3Mem2MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","2048");
}

void Amiga::on_z3Mem4MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","4096");
}

void Amiga::on_z3Mem8MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","8192");
}

void Amiga::on_z3Mem16MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","16384");
}

void Amiga::on_z3Mem32MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","32768");
}

void Amiga::on_z3Mem64MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","65536");
}

void Amiga::on_z3Mem128MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","131072");
}

void Amiga::on_z3Mem256MbRadio_clicked()
{
    this->ramConfiguration.setParameter("zorro_iii_memory","262144");
}
