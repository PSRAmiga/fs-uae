#include "amiga.h"
#include "ui_amiga.h"
#include <sstream>
#include <fstream>
#include <QUrl>
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QProcess>
#include <cstdlib>
using namespace std;

Amiga::Amiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amiga)
{
    ui->setupUi(this);
    ui->Setup->setCurrentIndex(0);
}

Amiga::~Amiga()
{
    delete ui;
}


void Amiga::on_kickstartFileToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Image adf/rom(*.adf *.rom)"));
    ui->kickstartFileLineEdit->setText(fileName);
    chipsetConfiguration.setParameter("kickstart_file",fileName.toStdString());
}

void Amiga::on_kickstartExtFileToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Image ROM(*.rom)"));
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

void Amiga::saveConfigInFile(string fileName){
    //TODO devo controllare gli errore sulla scrittura/lettura /////////////////////////////////////////////////////////////////////////////////

    ofstream myfile;
    myfile.open(fileName.c_str(),ios::out);

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

    if (!isEmptyString(floppyConfiguration.getFloppyDrive0ConfigString())) {myfile << floppyConfiguration.getFloppyDrive0ConfigString() << endl;}
    if (!isEmptyString(floppyConfiguration.getFloppyDrive1ConfigString())) {myfile << floppyConfiguration.getFloppyDrive1ConfigString() << endl;}
    if (!isEmptyString(floppyConfiguration.getFloppyDrive2ConfigString())) {myfile << floppyConfiguration.getFloppyDrive2ConfigString() << endl;}
    if (!isEmptyString(floppyConfiguration.getFloppyDrive3ConfigString())) {myfile << floppyConfiguration.getFloppyDrive3ConfigString() << endl;}
    if (!isEmptyString(floppyConfiguration.getFloppyDriveSpeedConfigString())) {myfile << floppyConfiguration.getFloppyDriveSpeedConfigString() << endl;}
    if (!isEmptyString(floppyConfiguration.getFloppyDriveVolumeConfigString())) {myfile << floppyConfiguration.getFloppyDriveVolumeConfigString() << endl;}
    if (floppyConfiguration.getFloppyImageSize()>0){
        for(int i=0;i<floppyConfiguration.getFloppyImageSize();i++){
            myfile << "floppy_image_" << i << " = " << floppyConfiguration.getFloppyImageAt(i) << endl;
        }

    }

    myfile.close();
}

void Amiga::on_saveConfigToolButton_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this, tr("Save file as"), QDir::homePath(), tr("Config file *.fs-uae (*.fs-uae)"));
    if (fileName.compare("")==0) {return; }

    //fare check sull'estensione
    string fileNameString;

    if(fileName.contains(".fs-uae", Qt::CaseInsensitive)) {fileNameString=fileName.toStdString();}
    else {fileNameString=fileName.toStdString()+".fs-uae";}

    saveConfigInFile(fileNameString);

}

int Amiga::getConfigurationAreaFromParameterName(string parameterName){
    //per ora ritorno un numero/una stringa poi magari potrei fare una configurazione astratta e ritornare direttamente l'oggetto chipsetConfiguration.
    //ovviamente tutte le config dovranno implemntare l'astratta così questa funzione ritorna un oggetto di tipo padre abstract config
    //e posso fare abstrobj.setParameter(...) con un'unica riga dentro a parseLine()
    if ((parameterName.compare("amiga_model")==0)||(parameterName.compare("accuracy")==0)||(parameterName.compare("kickstart_file")==0)||(parameterName.compare("kickstart_ext_file")==0)||(parameterName.compare("ntsc_mode")==0)) {
        return 1;
    } else if ((parameterName.compare("chip_memory")==0)||(parameterName.compare("slow_memory")==0)||(parameterName.compare("fast_memory")==0)||(parameterName.compare("zorro_iii_memory")==0)){
        return 2;
    } else if ((parameterName.substr(0,parameterName.length()-1).compare("floppy_drive_")==0)||(parameterName.substr(0,parameterName.length()-1).compare("floppy_image_")==0)||(parameterName.substr(0,parameterName.length()-2).compare("floppy_image_")==0)||(parameterName.compare("floppy_drive_volume")==0)||(parameterName.compare("floppy_drive_speed")==0)){
        //QMessageBox::about(this, tr("Error"),QString::fromStdString(parameterName.substr(0,parameterName.length()-1)));
        return 3;
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

    //NB se non trovo nessun parametro con quel nome significa che il parametro non esiste (getConfigurationAreaFromParameterName ritorna -1)
    //se invece il parametro esiste ma non è un valore valido se ne preoccupa l'area di configurazione
    int configArea=getConfigurationAreaFromParameterName(parameterName);
    if (configArea==1){
        chipsetConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==2){
        ramConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==3){
        floppyConfiguration.setParameter(parameterName,parameterValue);
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
        setFastMemoryDisabled(true);
    } else if (chip_memory.compare("4096")==0){
        ui->chipMem4MbRadio->setChecked(true);
        setFastMemoryDisabled(true);
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

    //ZORRO MEMORY
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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //FLOPPY DRIVES
    string floppy_drive_0=this->floppyConfiguration.getFloppyDrive0String();
    ui->floppyDrive0LineEdit->setText(QString::fromStdString(floppy_drive_0));

    string floppy_drive_1=this->floppyConfiguration.getFloppyDrive1String();
    ui->floppyDrive1LineEdit->setText(QString::fromStdString(floppy_drive_1));

    string floppy_drive_2=this->floppyConfiguration.getFloppyDrive2String();
    ui->floppyDrive2LineEdit->setText(QString::fromStdString(floppy_drive_2));

    string floppy_drive_3=this->floppyConfiguration.getFloppyDrive3String();
    ui->floppyDrive3LineEdit->setText(QString::fromStdString(floppy_drive_3));

    //FLOPPY DRIVE VOLUME
    string floppy_drive_volume=this->floppyConfiguration.getFloppyDriveVolumeString();
    ui->floppyDriveVolumeDisplayLabel->setText(QString::fromStdString(floppy_drive_volume));
    istringstream buffer(floppy_drive_volume);
    int intValue;
    buffer >> intValue;
    ui->floppyDriveVolumeSlider->setValue(intValue);

    //FLOPPY DRIVE SPEED
    //0<floppy_drive_speed<1200
    string floppy_drive_speed=this->floppyConfiguration.getFloppyDriveSpeedString();
    istringstream buffer2(floppy_drive_speed);
    int intValue2;
    buffer2 >> intValue2;
    ui->floppyDriveSpeedSlider->setValue(intValue2/100);
    string displayString;
    if (intValue2==0){
        displayString="TURBO";
    } else{
        displayString=floppy_drive_speed.substr(0,floppy_drive_speed.length()-2) + "X";
    }
    ui->floppyDriveSpeedDisplayLabel->setText(QString::fromStdString(displayString));

    ui->floppyDriveVolumeMuteCheckBox->setChecked(false);

    //FLOPPY SWAP IMAGES
    ui->floppySwappingImagesListWidget->clear();
    if (floppyConfiguration.getFloppyImageSize()>0){
        for(int i=0;i<floppyConfiguration.getFloppyImageSize();i++){
            ui->floppySwappingImagesListWidget->addItem(QString::fromStdString(floppyConfiguration.getFloppyImageAt(i)));
        }

    }
    string floppyOccupiedSlotsString=static_cast<ostringstream*>( &(ostringstream() << floppyConfiguration.getFloppyImageSize()) )->str();
    ui->floppyOccupiedSlotsDisplayLabel->setText(QString::fromStdString(floppyOccupiedSlotsString+"/20"));
}

void Amiga::on_loadConfigToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Config file *.fs-uae (*.fs-uae)"));
    if (fileName.compare("")==0) {return; }

    //devo resettare tutte le impostazioni a default perchè nel file i valori di defult non sono esplicitamente salvati
    //quindi rischierei di vedere i valori dell'ultima config

    chipsetConfiguration.setToDefaultConfiguration();
    ramConfiguration.setToDefaultConfiguration();
    floppyConfiguration.setToDefaultConfiguration();
    /////////////////////////////////////////////ecc per tutti gli altri///////////////////////////////////////////////////

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
    floppyConfiguration.setToDefaultConfiguration();
    /////////////////////////////////////////////ecc per tutti gli altri///////////////////////////////////////////////////


    //devo DISABILITARE/SVUOTARE KICK_EXT_DIR e tutte le cose che di default sarebbero disabilitate/vuote!
    setFastMemoryDisabled(false);
    // ui->floppySwappingImagesListWidget->clear();

    updateGraphicsFromInternalConfiguration();

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

void Amiga::on_runConfigButton_clicked()
{
    saveConfigInFile(".current.fs-uae");
    int returnValue=system("fs-uae .current.fs-uae");
    if (returnValue!=0)
    {
        ui->errorLabel->setText(QString::fromStdString("Ops...something went wrong :-("));
    }
}

void Amiga::on_actionAmiga_triggered()
{
    ui->Setup->setCurrentIndex(8);
}

void Amiga::on_actionSummary_triggered()
{
    string username="";
    register struct passwd *pw;
    register uid_t uid;
    uid = geteuid ();
    pw = getpwuid (uid);
    if (pw)
    {
        username=pw->pw_name;
    }

    string index="file:///home/"+username+"/.FS-UAE/html/index.html";
    QDesktopServices::openUrl(QUrl(QString::fromStdString(index), QUrl::TolerantMode));
}

void Amiga::on_floppyDrive0ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("ADF/IPF File(*.adf *.ipf)"));
    ui->floppyDrive0LineEdit->setText(fileName);
    floppyConfiguration.setParameter("floppy_drive_0",fileName.toStdString());
}

void Amiga::on_floppyDrive1ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("ADF/IPF File(*.adf *.ipf)"));
    ui->floppyDrive1LineEdit->setText(fileName);
    floppyConfiguration.setParameter("floppy_drive_1",fileName.toStdString());
}

void Amiga::on_floppyDrive2ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("ADF/IPF File(*.adf *.ipf)"));
    ui->floppyDrive2LineEdit->setText(fileName);
    floppyConfiguration.setParameter("floppy_drive_2",fileName.toStdString());
}

void Amiga::on_floppyDrive3ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("ADF/IPF File(*.adf *.ipf)"));
    ui->floppyDrive3LineEdit->setText(fileName);
    floppyConfiguration.setParameter("floppy_drive_3",fileName.toStdString());
}


void Amiga::on_floppySwappingImagesAddPushButton_clicked()
{
    if (ui->floppySwappingImagesListWidget->count()==20){
        QMessageBox::about(this, tr("Error"),tr("You can select at most 20 floppies"));
        return;}
    QStringList fileNames=QFileDialog::getOpenFileNames(this, tr("Open file"), QDir::homePath(), tr("ADF File(*.adf)"));

    if (fileNames.count()==0){
        //hai premuto annulla
        return;}

    if (fileNames.count()+ui->floppySwappingImagesListWidget->count()>20){
        QMessageBox::about(this, tr("Error"),tr("You can select at most 20 floppies"));
        return;}

    for(int i=0;i<fileNames.count();i++){
        //aggiorno la lista interna
        floppyConfiguration.pushBackFloppyImage(fileNames.at(i).toStdString());
        //aggiorno la lista grafica
        //  ui->floppySwappingImagesListWidget->addItem(fileNames.at(i));
    }
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_floppySwappingImagerRemovePushButton_clicked()
{
    //devo rimuovere i selezionati dalla lista interna
    QItemSelectionModel *selection = ui->floppySwappingImagesListWidget->selectionModel();
    QModelIndexList indexes = selection->selectedRows();
    QListIterator<QModelIndex> i(indexes);
    QList <int> indexList;
    while(i.hasNext())
    {
        QModelIndex index = i.next();
        indexList << index.row();

    };
    //il problema è che avendo la lista crescente di indici degli elementi da togliere non potevo partire dal più piccolo: x es
    //se ho [1,4,7] e tolgo il #1 poi quando elimino il #4 in realtà sto eliminando il 5, quindi devo partire dal #7 e scendere
    for(int x=indexList.size()-1;x>=0;x--){
        floppyConfiguration.eraseFloppyImageAt(indexList[x]);
    }

    //svuoto lista grafica
    ui->floppySwappingImagesListWidget->clear();

    //aggiorno la grafica
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_floppyDriveVolumeSlider_valueChanged(int value)
{
    string stringvalue=static_cast<ostringstream*>( &(ostringstream() << value) )->str();

    floppyConfiguration.setParameter("floppy_drive_volume",stringvalue);
    ui->floppyDriveVolumeDisplayLabel->setText(QString::fromStdString(floppyConfiguration.getFloppyDriveVolumeString()));
}

void Amiga::on_floppyDriveVolumeMuteCheckBox_clicked()
{
    if(ui->floppyDriveVolumeMuteCheckBox->isChecked()){
        ui->floppyDriveVolumeDisplayLabel->setText("0");
        ui->floppyDriveVolumeSlider->setEnabled(false);
        floppyConfiguration.setParameter("floppy_drive_volume","0");
    } else {
        string stringvalue=static_cast<ostringstream*>( &(ostringstream() << ui->floppyDriveVolumeSlider->value()) )->str();
        ui->floppyDriveVolumeDisplayLabel->setText(QString::fromStdString(stringvalue));
        ui->floppyDriveVolumeSlider->setEnabled(true);
        floppyConfiguration.setParameter("floppy_drive_volume",stringvalue);
    }
}

void Amiga::on_floppyDriveSpeedSlider_valueChanged(int position)
{
    //0<=position<=12
    string positionString=static_cast<ostringstream*>( &(ostringstream() << position) )->str();
    string stringvalue=static_cast<ostringstream*>( &(ostringstream() << position*100) )->str();
    floppyConfiguration.setParameter("floppy_drive_speed",stringvalue);
    string displayString;
    if (position==0){
        displayString="TURBO";
    } else{
        displayString=positionString+"X";
    }
    ui->floppyDriveSpeedDisplayLabel->setText(QString::fromStdString(displayString));
}




void Amiga::on_alternativeBaseDirPushButton_clicked()
{
    //QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/", QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);

}
