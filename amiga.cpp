/*! \file amiga.cpp
 amiga.cpp

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 Written by Riva Alessandro Mario, alessandromario.riva@gmail.com
 and Sanvito Davide, dsanvito90@gmail.com. */
#include "amiga.h"
#include "ui_amiga.h"
#include <sstream>
#include <fstream>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <cstdlib>

#include <QKeyEvent>

#include <QApplication>
#include <QDesktopWidget>
#include <sys/stat.h>
using namespace std;

void static showAlert(string message){
    QMessageBox msg;
    msg.setText(QString::fromStdString(message));
    msg.exec();
}

void static checkFoldersExistence(){
    char *username=getenv("USER");
    struct stat st;
    string italianFolder="/home/"+string(username)+"/Documenti/FS-UAE";     //per testare il msg d'errore scrivere Documenti con la D minuscola
    string englishFolder="/home/"+string(username)+"/Documents/FS-UAE";
    if ((stat(italianFolder.c_str(),&st) != 0)&&(stat(englishFolder.c_str(),&st) != 0)){
        showAlert("FS-UAE folders not found. You must start FS-UAE for the first time to create FS-UAE folders. FS-UAE wil be now launched.\nPress F12 to enter menu, then navigate to the X button in the top right corner with the cursor keys and finally press Return to quit FS-UAE.");
        int returnValue=system("fs-uae"); //per testare il msg d'errore fare system("fs-uaeeee")
        if (returnValue!=0){
            showAlert("FS-UAE is not installed in your system, please install it and relaunch this application.");
            exit(0);
        }
    }
}

Amiga::Amiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amiga)
{
    ui->setupUi(this);

    //things to do onLoad

    checkFoldersExistence();

    loadDefaultValues();

    ui->mainTabWidget->setCurrentIndex(0);
    //acquire current screen resolution
    ui->fullscreenResolutionXSpinBox->setValue(QApplication::desktop()->width());
    ui->fullscreenResolutionYSpinBox->setValue(QApplication::desktop()->height());
    //allow only numeric input
    ui->audioBufferLineEdit->setValidator(new QIntValidator(ui->audioBufferLineEdit));
    ui->serverPortLineEdit->setValidator(new QIntValidator(ui->serverPortLineEdit));
    ui->mouseSpeedLineEdit->setValidator(new QIntValidator(ui->mouseSpeedLineEdit));
    //allow only numeric or * input
    QRegExp rx("[*]|[0-9]{1,4}");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->viewportIn1LineEdit->setValidator(validator);
    ui->viewportIn2LineEdit->setValidator(validator);
    ui->viewportIn3LineEdit->setValidator(validator);
    ui->viewportIn4LineEdit->setValidator(validator);
    ui->viewportOut1LineEdit->setValidator(validator);
    ui->viewportOut2LineEdit->setValidator(validator);
    ui->viewportOut3LineEdit->setValidator(validator);
    ui->viewportOut4LineEdit->setValidator(validator);
}

Amiga::~Amiga()
{
    delete ui;
}

int strToInt(string s){
    istringstream buffer(s);
    int intValue;
    buffer >> intValue;
    return intValue;
}

float strToFloat(string line){
    float valor;
    stringstream stream(line);
    stream >> valor;
    return valor;
}

string intToStr(int n){
    return static_cast<ostringstream*>( &(ostringstream() << n) )->str();
}

/////////////////////////////////////////////////////////////////////

bool isEmptyString(string s){
    //NB compare ritorna 0 se è la comparazione è vera, è il contrario!
    return (s.compare("")==0);
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

    for(int i=0;i<4;i++){
        if (!isEmptyString(floppyConfiguration.getFloppyDriveConfigStringAt(i))) {myfile << floppyConfiguration.getFloppyDriveConfigStringAt(i) << endl;}
    }
    if (!isEmptyString(floppyConfiguration.getFloppyDriveSpeedConfigString())) {myfile << floppyConfiguration.getFloppyDriveSpeedConfigString() << endl;}
    if (!isEmptyString(floppyConfiguration.getFloppyDriveVolumeConfigString())) {myfile << floppyConfiguration.getFloppyDriveVolumeConfigString() << endl;}
    if (floppyConfiguration.getFloppyImageSize()>0){
        for(int i=0;i<floppyConfiguration.getFloppyImageSize();i++){
            myfile << "floppy_image_" << i << " = " << floppyConfiguration.getFloppyImageAt(i) << endl;
        }
    }

    if (!isEmptyString(cdromConfiguration.getCDRomDrive0ConfigString())) {myfile << cdromConfiguration.getCDRomDrive0ConfigString() << endl;}
    if (cdromConfiguration.getCDRomImageSize()>0){
        for(int i=0;i<cdromConfiguration.getCDRomImageSize();i++){
            myfile << "cdrom_image_" << i << " = " << cdromConfiguration.getCDRomImageAt(i) << endl;
        }
    }

    for(int i=0;i<10;i++){
        if (!isEmptyString(hardDiskConfiguration.getHardDriveConfigStringAt(i))) {myfile << hardDiskConfiguration.getHardDriveConfigStringAt(i) << endl;}
        if (!isEmptyString(hardDiskConfiguration.getHardDriveLabelConfigStringAt(i))) {myfile << hardDiskConfiguration.getHardDriveLabelConfigStringAt(i) << endl;}
        if (!isEmptyString(hardDiskConfiguration.getHardDriveReadOnlyConfigStringAt(i))) {myfile << hardDiskConfiguration.getHardDriveReadOnlyConfigStringAt(i) << endl;}
    }

    if (!isEmptyString(graphicsConfiguration.getFullscreenConfigString())) {myfile << graphicsConfiguration.getFullscreenConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getWindowResizableConfigString())) {myfile << graphicsConfiguration.getWindowResizableConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getKeepAspectConfigString())) {myfile << graphicsConfiguration.getKeepAspectConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getFullscreenWidthConfigString()) && intToStr(QApplication::desktop()->width()).compare(graphicsConfiguration.getFullscreenWidthString())) {myfile << graphicsConfiguration.getFullscreenWidthConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getFullscreenHeightConfigString()) && intToStr(QApplication::desktop()->height()).compare(graphicsConfiguration.getFullscreenHeightString())) {myfile << graphicsConfiguration.getFullscreenHeightConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getWindowWidthConfigString())) {myfile << graphicsConfiguration.getWindowWidthConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getWindowHeightConfigString())) {myfile << graphicsConfiguration.getWindowHeightConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getFsaaConfigString())) {myfile << graphicsConfiguration.getFsaaConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getScanlinesConfigString())) {myfile << graphicsConfiguration.getScanlinesConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getRtgScanlinesConfigString())) {myfile << graphicsConfiguration.getRtgScanlinesConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getScanlinesDarkConfigString())) {myfile << graphicsConfiguration.getScanlinesDarkConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getScanlinesLightConfigString())) {myfile << graphicsConfiguration.getScanlinesLightConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getShaderConfigString())) {myfile << graphicsConfiguration.getShaderConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getLowResolutionConfigString())) {myfile << graphicsConfiguration.getLowResolutionConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getLineDoublingConfigString())) {myfile << graphicsConfiguration.getLineDoublingConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getScaleXConfigString())) {myfile << graphicsConfiguration.getScaleXConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getScaleYConfigString())) {myfile << graphicsConfiguration.getScaleYConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getAlignXConfigString())) {myfile << graphicsConfiguration.getAlignXConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getAlignYConfigString())) {myfile << graphicsConfiguration.getAlignYConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getZoomConfigString())) {myfile << graphicsConfiguration.getZoomConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getTextureFilterConfigString())) {myfile << graphicsConfiguration.getTextureFilterConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getVideoSyncConfigString())) {myfile << graphicsConfiguration.getVideoSyncConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getVideoSyncMethodConfigString())) {myfile << graphicsConfiguration.getVideoSyncMethodConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getVideoFormatConfigString())) {myfile << graphicsConfiguration.getVideoFormatConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getTextureFormatConfigString())) {myfile << graphicsConfiguration.getTextureFormatConfigString() << endl;}
    if (!isEmptyString(graphicsConfiguration.getViewportConfigString())) {myfile << graphicsConfiguration.getViewportConfigString() << endl;}

    if (!isEmptyString(miscConfiguration.getInputGrabConfigString())) {myfile << miscConfiguration.getInputGrabConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getAutomaticInputGrabConfigString())) {myfile << miscConfiguration.getAutomaticInputGrabConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getBsdSocketLibraryConfigString())) {myfile << miscConfiguration.getBsdSocketLibraryConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getAudioBufferConfigString())) {myfile << miscConfiguration.getAudioBufferConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getMouseSpeedConfigString())) {myfile << miscConfiguration.getMouseSpeedConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getTitleConfigString())) {myfile << miscConfiguration.getTitleConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getSubTitleConfigString())) {myfile << miscConfiguration.getSubTitleConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getNetPlayServerConfigString())) {myfile << miscConfiguration.getNetPlayServerConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getNetPlayPortConfigString())) {myfile << miscConfiguration.getNetPlayPortConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getNetPlayTagConfigString())) {myfile << miscConfiguration.getNetPlayTagConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getNetPlayPasswordConfigString())) {myfile << miscConfiguration.getNetPlayPasswordConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getBaseDirConfigString())) {myfile << miscConfiguration.getBaseDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getKickstartsDirConfigString())) {myfile << miscConfiguration.getKickstartsDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getSaveStatesDirConfigString())) {myfile << miscConfiguration.getSaveStatesDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getFloppyOverlaysDirConfigString())) {myfile << miscConfiguration.getFloppyOverlaysDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getFlashMemoryDirConfigString())) {myfile << miscConfiguration.getFlashMemoryDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getControllersDirConfigString())) {myfile << miscConfiguration.getControllersDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getLogsDirConfigString())) {myfile << miscConfiguration.getLogsDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getHardDrivesDirConfigString())) {myfile << miscConfiguration.getHardDrivesDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getCDRomsDirConfigString())) {myfile << miscConfiguration.getCDRomsDirConfigString() << endl;}
    if (!isEmptyString(miscConfiguration.getFloppiesDirConfigString())) {myfile << miscConfiguration.getFloppiesDirConfigString() << endl;}

    if (!isEmptyString(themeConfiguration.getOverlayImageConfigString())) {myfile << themeConfiguration.getOverlayImageConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getThemeConfigString())) {myfile << themeConfiguration.getThemeConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getFadeColorConfigString())) {myfile << themeConfiguration.getFadeColorConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getFloorColor1ConfigString())) {myfile << themeConfiguration.getFloorColor1ConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getFloorColor2ConfigString())) {myfile << themeConfiguration.getFloorColor2ConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getHeadingColorConfigString())) {myfile << themeConfiguration.getHeadingColorConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getWallColor1ConfigString())) {myfile << themeConfiguration.getWallColor1ConfigString() << endl;}
    if (!isEmptyString(themeConfiguration.getWallColor2ConfigString())) {myfile << themeConfiguration.getWallColor2ConfigString() << endl;}

    if (inputConfiguration.getCustomInputMappingSize()>0){
        for(int i=0;i<inputConfiguration.getCustomInputMappingSize();i++){
            myfile << inputConfiguration.getCustomInputMappingAt(i) << endl;
        }
    }

    if (!isEmptyString(inputConfiguration.getJoystickPort0ConfigString())) {myfile << inputConfiguration.getJoystickPort0ConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort1ConfigString())) {myfile << inputConfiguration.getJoystickPort1ConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort2ConfigString())) {myfile << inputConfiguration.getJoystickPort2ConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort3ConfigString())) {myfile << inputConfiguration.getJoystickPort3ConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort0ModeConfigString())) {myfile << inputConfiguration.getJoystickPort0ModeConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort1ModeConfigString())) {myfile << inputConfiguration.getJoystickPort1ModeConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort2ModeConfigString())) {myfile << inputConfiguration.getJoystickPort2ModeConfigString() << endl;}
    if (!isEmptyString(inputConfiguration.getJoystickPort3ModeConfigString())) {myfile << inputConfiguration.getJoystickPort3ModeConfigString() << endl;}

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

    checkConfigurationConsistency();// --> devo eliminare le configurazioni proibite che potrebbero essere venute fuori dal caricamento di un file manomeso

    updateGraphicsFromInternalConfiguration();

    saveConfigInFile(fileNameString);
}

void Amiga::parseLine(string line){
    if (line.length()<=1) return;
    //fs-uae config file convention is "name = value"

    //int separatorPosition=line.find_first_of(" = ");
    int separatorPosition=line.find(" = ");
    string parameterName=line.substr(0,separatorPosition);
    string parameterValue=line.substr(separatorPosition+3,line.length()-1);

    //bisogna capire in quale area di configurazione indirizzarlo
    //NB se non trovo nessun parametro con quel nome significa che il parametro non esiste
    //MA se invece il parametro esiste ma non ha un valore valido se ne preoccupa l'area di configurazione

    if (chipsetConfiguration.hasParameter(parameterName)){
        if (chipsetConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (ramConfiguration.hasParameter(parameterName)){
        if (ramConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (floppyConfiguration.hasParameter(parameterName)){
        if (floppyConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (cdromConfiguration.hasParameter(parameterName)){
        if (cdromConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (hardDiskConfiguration.hasParameter(parameterName)){
        if (hardDiskConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (inputConfiguration.hasParameter(parameterName)){
        if (inputConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (graphicsConfiguration.hasParameter(parameterName)){
        if (graphicsConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (themeConfiguration.hasParameter(parameterName)){
        if (themeConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    } else if (miscConfiguration.hasParameter(parameterName)){
        if (miscConfiguration.setParameter(parameterName,parameterValue)==-1){
            showAlert("\""+parameterValue+"\" is an invalid value for \""+parameterName+"\"");
        }
    }
}

void Amiga::checkConfigurationConsistency()
{
    string message="Following configuration inconsistencies have been found and resolved:\n\n";

    string amiga_model=chipsetConfiguration.getAmigaModelString();
    if ((amiga_model.compare("CD32")!=0)&&(amiga_model.compare("CDTV")!=0)){
        //CD section is enabled only if model is CD32 or CDTV
        if((cdromConfiguration.getCDRomDrive0String().compare("")!=0)||(cdromConfiguration.getCDRomImageSize()>0)){
            message.append("-"+amiga_model+" hasn't any CD drive --> you can't select any CDrom image\n");
            cdromConfiguration.setToDefaultConfiguration();
        }
        //Kickstart Extended ROm is only available witch CD32 and CDTV
        if(chipsetConfiguration.getKickstartExtFileString().compare("")!=0){
            message.append("-Extended kickstart ROM are only available with CD32 and CDTV model\n");
            chipsetConfiguration.setParameter("kickstart_ext_file","");
        }
    }
    if ((amiga_model.compare("A1200/020")==0)||(amiga_model.compare("A4000/040")==0)||(amiga_model.compare("CD32")==0)){
        //slowmemory 1.8MB is disabled with A1200/020, A4000/040 e CD32 model
        if(ramConfiguration.getSlowMemoryString().compare("1792")==0){
            message.append("-You can't select 1.8MB slowmemory with "+amiga_model+" model\n");
            ramConfiguration.setParameter("slow_memory","NONE");
        }
    }
    if ((amiga_model.compare("A1200/020")!=0)&&(amiga_model.compare("A4000/040")!=0)){
        //Zorro3 is enabled only if model is A1200/020 or A4000/040
        if(ramConfiguration.getZorro3String().compare("NONE")!=0){
            message.append("-"+amiga_model+" hasn't ZorroIII memory --> you can't select a value different from NONE\n");
            ramConfiguration.setParameter("zorro_iii_memory","NONE");
        }
    }
    if((ramConfiguration.getChipMemoryString().compare("4096")==0) || (ramConfiguration.getChipMemoryString().compare("8192")==0)){
        //fastmemory is disabled if chipsetram=4MB or 8MB
        if(ramConfiguration.getFastMemoryString().compare("NONE")!=0){
            message.append("-You can't select any Fastmemory if Chipset memory is 4MB or 8MB\n");
            this->ramConfiguration.setParameter("fast_memory","NONE");
        }
    }
    for(int i=0;i<10;i++){
        //HD's label and readonly flag can be setted only if HD isn't empty
        if(hardDiskConfiguration.getHardDriveStringAt(i).compare("")==0){
            if(hardDiskConfiguration.getHardDriveLabelStringAt(i).compare("")!=0){
                message.append("-Hard Disk "+intToStr(i)+" is empty --> you can't set its Label\n");
                this->hardDiskConfiguration.setParameter("hard_drive_"+intToStr(i)+"_label","");
            }
            if(hardDiskConfiguration.getHardDriveReadOnlyStringAt(i).compare("0")!=0){
                message.append("-Hard Disk "+intToStr(i)+" is empty --> you can't set its Readonly flag\n");
                this->hardDiskConfiguration.setParameter("hard_drive_"+intToStr(i)+"_read_only","0");
            }
        }
    }

    //Priority is given from left to right (0-1-2-3)
    if((inputConfiguration.getJoystickPort1String().compare("mouse")==0)&&(inputConfiguration.getJoystickPort0String().compare("mouse")==0)){
        message.append("-Mouse is already selected on Port 0 --> you can't set another mouse on Port 1\n");
        this->inputConfiguration.setParameter("joystick_port_1","keyboard");
    }
    if((inputConfiguration.getJoystickPort1String().compare("keyboard")==0)&&(inputConfiguration.getJoystickPort0String().compare("keyboard")==0)){
        message.append("-Keyboard is already selected on Port 0 --> you can't set another keyboard on Port 1\n");
        this->inputConfiguration.setParameter("joystick_port_1","mouse");
    }

    if(inputConfiguration.getJoystickPort2String().compare("mouse")==0){
        if ((inputConfiguration.getJoystickPort0String().compare("mouse")==0)||(inputConfiguration.getJoystickPort1String().compare("mouse")==0)){
            message.append("-Mouse is already selected on Port 0 or 1 --> you can't set another mouse on Port 2\n");
            this->inputConfiguration.setParameter("joystick_port_2","none");
        }
    }
    if(inputConfiguration.getJoystickPort2String().compare("keyboard")==0){
        if ((inputConfiguration.getJoystickPort0String().compare("keyboard")==0)||(inputConfiguration.getJoystickPort1String().compare("keyboard")==0)){
            message.append("-Keyboard is already selected on Port 0 or 1 --> you can't set another keyboard on Port 2\n");
            this->inputConfiguration.setParameter("joystick_port_2","none");
        }
    }

    if(inputConfiguration.getJoystickPort3String().compare("mouse")==0){
        if ((inputConfiguration.getJoystickPort0String().compare("mouse")==0)||(inputConfiguration.getJoystickPort1String().compare("mouse")==0)||(inputConfiguration.getJoystickPort2String().compare("mouse")==0)){
            message.append("-Mouse is already selected on Port 0, 1 or 2 --> you can't set another mouse on Port 3\n");
            this->inputConfiguration.setParameter("joystick_port_3","none");
        }
    }
    if(inputConfiguration.getJoystickPort3String().compare("keyboard")==0){
        if ((inputConfiguration.getJoystickPort0String().compare("keyboard")==0)||(inputConfiguration.getJoystickPort1String().compare("keyboard")==0)||(inputConfiguration.getJoystickPort2String().compare("keyboard")==0)){
            message.append("-Keyboard is already selected on Port 0, 1 or 2 --> you can't set another keyboard on Port 3\n");
            this->inputConfiguration.setParameter("joystick_port_3","none");
        }
    }

    /*
    NNB la consistenza non si preoccupa della grafica (disabilitazioni varie) ma dello stato interno. va quindi eseguita PRIMA per preparare
    l'aggiornamento della grafica DALLO stato interno. Viceversa updateGraphics() non tocca lo stato interno però sa cosa abilitare/disabilitare
    */

    if (message.compare("Following configuration inconsistencies have been found and resolved:\n\n")==0){
        return;}
    message.append("\n\nPlease note that the configuration file has NOT been modified.");
    showAlert(message);
}

void Amiga::updateGraphicsFromInternalConfiguration(){
    //ACCURACY
    string accuracy=chipsetConfiguration.getAccuracyString();
    if (accuracy.compare("-1")==0){
        ui->accuracyLeastRadio->setChecked(true);
    } else if (accuracy.compare("0")==0){
        ui->accuracyNormalRadio->setChecked(true);
    } else {
        ui->accuracyMostadio->setChecked(true);
    }

    //NTSC MODE
    string ntsc_mode=chipsetConfiguration.getNTSCModeString();
    if (ntsc_mode.compare("1")==0){
        ui->videoModeNTSCRadio->setChecked(true);
    } else {
        ui->videoModePALRadio->setChecked(true);
    }

    //AMIGA MODEL
    string amiga_model=chipsetConfiguration.getAmigaModelString();
    if(ui->amigaModelComboBox->findText(QString::fromStdString(amiga_model),Qt::MatchExactly)!=-1){
        ui->amigaModelComboBox->setCurrentIndex(ui->amigaModelComboBox->findText(QString::fromStdString(amiga_model),Qt::MatchExactly));
    } else {ui->amigaModelComboBox->setCurrentIndex(0); }

    if ((amiga_model.compare("CD32")==0)||(amiga_model.compare("CDTV")==0))
    {
        ui->kickstartExtFileLabel->setEnabled(true);
        ui->kickstartExtFileLineEdit->setEnabled(true);
        ui->kickstartExtFileToolButton->setEnabled(true);

        ui->cdromDrive0Label->setEnabled(true);
        ui->cdromDrive0LineEdit->setEnabled(true);
        ui->cdromDrive0ToolButton->setEnabled(true);
        ui->cdromSwappingImagesLabel->setEnabled(true);
        ui->cdromSwappingImagesListWidget->setEnabled(true);
        ui->cdromSwappingImagesRemovePushButton->setEnabled(true);
        ui->cdromSwappingImagesAddPushButton->setEnabled(true);
        ui->cdromOccupiedSlotsLabel->setEnabled(true);
        ui->cdromOccupiedSlotsDisplayLabel->setEnabled(true);
    } else
    {
        ui->kickstartExtFileLabel->setEnabled(false);
        ui->kickstartExtFileLineEdit->setEnabled(false);
        ui->kickstartExtFileToolButton->setEnabled(false);

        ui->cdromDrive0Label->setEnabled(false);
        ui->cdromDrive0LineEdit->setEnabled(false);
        ui->cdromDrive0ToolButton->setEnabled(false);
        ui->cdromSwappingImagesLabel->setEnabled(false);
        ui->cdromSwappingImagesListWidget->setEnabled(false);
        ui->cdromSwappingImagesRemovePushButton->setEnabled(false);
        ui->cdromSwappingImagesAddPushButton->setEnabled(false);
        ui->cdromOccupiedSlotsLabel->setEnabled(false);
        ui->cdromOccupiedSlotsDisplayLabel->setEnabled(false);
    }

    if ((amiga_model.compare("A1200/020")==0)||(amiga_model.compare("A4000/040")==0)||(amiga_model.compare("CD32")==0))
    {
        ui->slowMem1_8MbRadio->setDisabled(true);
    } else
    {
        ui->slowMem1_8MbRadio->setDisabled(false);
    }

    if ((amiga_model.compare("A1200/020")==0)||(amiga_model.compare("A4000/040")==0))
    {
        setZorroIIIMemoryDisabled(false);
    } else
    {
        setZorroIIIMemoryDisabled(true);
    }

    //KICKSTART ROM
    string kickstart_file=chipsetConfiguration.getKickstartFileString();
    ui->kickstartFileLineEdit->setText(QString::fromStdString(kickstart_file));

    //KICKSTART EXT ROM
    string kickstart_ext_file=chipsetConfiguration.getKickstartExtFileString();
    ui->kickstartExtFileLineEdit->setText(QString::fromStdString(kickstart_ext_file));

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////


    setFastMemoryDisabled(false);
    //CHIP MEMORY
    string chip_memory=ramConfiguration.getChipMemoryString();
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
    string slow_memory=ramConfiguration.getSlowMemoryString();
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
    string fast_memory=ramConfiguration.getFastMemoryString();
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
    string zorro_iii_memory=ramConfiguration.getZorro3String();
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
    for(int i=0;i<4;i++){
        string iString=intToStr(i);

        string floppy_drive=floppyConfiguration.getFloppyDriveStringAt(i);
        QLineEdit *lineEdit = ui->widget->findChild<QLineEdit *>(QString::fromStdString("floppyDrive" + iString + "LineEdit"));
        if (lineEdit !=0){
            lineEdit->setText(QString::fromStdString(floppy_drive));
        }
    }

    //FLOPPY DRIVE VOLUME
    string floppy_drive_volume=floppyConfiguration.getFloppyDriveVolumeString();
    ui->floppyDriveVolumeDisplayLabel->setText(QString::fromStdString(floppy_drive_volume));
    ui->floppyDriveVolumeSlider->setValue(strToInt(floppy_drive_volume));

    //FLOPPY DRIVE SPEED
    //0<floppy_drive_speed<1200
    string floppy_drive_speed=floppyConfiguration.getFloppyDriveSpeedString();
    ui->floppyDriveSpeedSlider->setValue(strToInt(floppy_drive_speed)/100);
    string displayString;
    if (strToInt(floppy_drive_speed)==0){
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
    string floppyOccupiedSlotsString=intToStr(floppyConfiguration.getFloppyImageSize());
    ui->floppyOccupiedSlotsDisplayLabel->setText(QString::fromStdString(floppyOccupiedSlotsString+"/20"));

    //CDROM DRIVE
    string cdrom_drive_0=cdromConfiguration.getCDRomDrive0String();
    ui->cdromDrive0LineEdit->setText(QString::fromStdString(cdrom_drive_0));

    //CDROM SWAP IMAGES
    ui->cdromSwappingImagesListWidget->clear();
    if (cdromConfiguration.getCDRomImageSize()>0){
        for(int i=0;i<cdromConfiguration.getCDRomImageSize();i++){
            ui->cdromSwappingImagesListWidget->addItem(QString::fromStdString(cdromConfiguration.getCDRomImageAt(i)));
        }

    }
    string cdromOccupiedSlotsString=intToStr(cdromConfiguration.getCDRomImageSize());
    ui->cdromOccupiedSlotsDisplayLabel->setText(QString::fromStdString(cdromOccupiedSlotsString+"/20"));

    //HARD DRIVES

    for(int i=0;i<10;i++){
        string iString=intToStr(i);

        string hardDriveString=hardDiskConfiguration.getHardDriveStringAt(i);
        QLineEdit *lineEdit = ui->widget->findChild<QLineEdit *>(QString::fromStdString("hardDrive" + iString + "LineEdit"));
        if (lineEdit !=0){
            lineEdit->setText(QString::fromStdString(hardDriveString));
        }

        string hardDriveLabelString=hardDiskConfiguration.getHardDriveLabelStringAt(i);
        lineEdit = ui->widget->findChild<QLineEdit *>(QString::fromStdString("hardDrive" + iString + "LabelLineEdit"));
        if (lineEdit !=0){
            lineEdit->setText(QString::fromStdString(hardDriveLabelString));
        }

        string isChecked=hardDiskConfiguration.getHardDriveReadOnlyStringAt(i);
        QCheckBox *checkBox = ui->widget->findChild<QCheckBox *>(QString::fromStdString("hardDrive" + iString + "ReadOnlyCheckBox"));
        if (checkBox !=0){
            if (isChecked.compare("1")==0){
                checkBox->setChecked(true);
            } else {
                checkBox->setChecked(false);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //FULLSCREEN
    string fullscreen=graphicsConfiguration.getFullscreenString();
    if(fullscreen.compare("1")==0){
        ui->displaySettingsStartFullscreenRadioButton->setChecked(true);
    } else {
        ui->displaySettingsStartFullscreenRadioButton->setChecked(false);
    }

    //RESIZABLE
    string resizable=graphicsConfiguration.getWindowResizableString();
    if(resizable.compare("0")==0){
        ui->displaySettingsResizableRadioButton->setChecked(false);
    } else {
        ui->displaySettingsResizableRadioButton->setChecked(true);
    }

    //KEEP ASPECT RATIO
    string keep_aspect=graphicsConfiguration.getKeepAspectString();
    if(keep_aspect.compare("1")==0){
        ui->displaySettingsKeepAspectRatioRadioButton->setChecked(true);
    } else {
        ui->displaySettingsKeepAspectRatioRadioButton->setChecked(false);
    }

    //SCANLINES
    string scanlines=graphicsConfiguration.getScanlinesString();
    if(scanlines.compare("1")==0){
        ui->scanlinesRadioButton->setChecked(true);
    } else {
        ui->scanlinesRadioButton->setChecked(false);
    }

    //RTG SCANLINES
    string scanlines_rtg=graphicsConfiguration.getRtgScanlinesString();
    if(scanlines_rtg.compare("1")==0){
        ui->scanlinesRTGRadioButton->setChecked(true);
    } else {
        ui->scanlinesRTGRadioButton->setChecked(false);
    }

    //LOW RESOLUTION
    string low_resolution=graphicsConfiguration.getLowResolutionString();
    if(low_resolution.compare("1")==0){
        ui->lowResolutionRadioButton->setChecked(true);
    } else {
        ui->lowResolutionRadioButton->setChecked(false);
    }

    //LINE DOUBLING
    string line_doubling=graphicsConfiguration.getLineDoublingString();
    if(line_doubling.compare("0")==0){
        ui->lineDoublingRadioButton->setChecked(false);
    } else {
        ui->lineDoublingRadioButton->setChecked(true);
    }

    //RESOLUTIONS
    string fullscreen_resolution_x=graphicsConfiguration.getFullscreenWidthString();
    if (isEmptyString(fullscreen_resolution_x)){
        ui->fullscreenResolutionXSpinBox->setValue(QApplication::desktop()->width());
    } else {ui->fullscreenResolutionXSpinBox->setValue(strToInt(fullscreen_resolution_x));
    }

    string fullscreen_resolution_y=graphicsConfiguration.getFullscreenHeightString();
    if (isEmptyString(fullscreen_resolution_y)){
        ui->fullscreenResolutionYSpinBox->setValue(QApplication::desktop()->height());
    } else {ui->fullscreenResolutionYSpinBox->setValue(strToInt(fullscreen_resolution_y));
    }

    string window_resolution_x=graphicsConfiguration.getWindowWidthString();
    ui->windowResolutionXSpinBox->setValue(strToInt(window_resolution_x));

    string window_resolution_y=graphicsConfiguration.getWindowHeightString();
    ui->windowResolutionYSpinBox->setValue(strToInt(window_resolution_y));

    //SCALE
    string scale_x=graphicsConfiguration.getScaleXString();
    ui->scaleXDoubleSpinBox->setValue(strToFloat(scale_x));

    string scale_y=graphicsConfiguration.getScaleYString();
    ui->scaleYDoubleSpinBox->setValue(strToFloat(scale_y));

    //ALIGN
    string align_x=graphicsConfiguration.getAlignXString();
    ui->alignXdoubleSpinBox->setValue(strToFloat(align_x));

    string align_y=graphicsConfiguration.getAlignYString();
    ui->alignYDoubleSpinBox->setValue(strToFloat(align_y));

    //FSAA
    string fsaa=graphicsConfiguration.getFsaaString();
    if (fsaa.compare("8")==0){
        ui->fullSceneAntiAliasing8xRadioButton->setChecked(true);
    } else if (fsaa.compare("4")==0){
        ui->fullSceneAntiAliasing4xRadioButton->setChecked(true);
    } else if (fsaa.compare("2")==0){
        ui->fullSceneAntiAliasing2xRadioButton->setChecked(true);
    } else {
        ui->fullSceneAntiAliasingOffRadioButton->setChecked(true);
    }

    //TEXTURE FILTER
    string texture_filter=graphicsConfiguration.getTextureFilterString();
    if (texture_filter.compare("nearest")==0){
        ui->textureFilterNearestRadioButton->setChecked(true);
    } else {
        ui->textureFilterLinearRadioButton->setChecked(true);
    }

    //ZOOM
    string zoom=graphicsConfiguration.getZoomString();
    ui->f11InitialModeWithBorderCheckBox->setDisabled(false);
    ui->f11InitialModeWithBorderCheckBox->setChecked(false);
    if (zoom.compare("640x512+border")==0){
        ui->f11InitalMode640x512RadioButton->setChecked(true);
        ui->f11InitialModeWithBorderCheckBox->setChecked(true);
    } else if (zoom.compare("640x512")==0){
        ui->f11InitalMode640x512RadioButton->setChecked(true);
    } else if (zoom.compare("640x480+border")==0){
        ui->f11InitalMode640x480RadioButton->setChecked(true);
        ui->f11InitialModeWithBorderCheckBox->setChecked(true);
    } else if (zoom.compare("640x480")==0){
        ui->f11InitalMode640x480RadioButton->setChecked(true);
    } else if (zoom.compare("640x400+border")==0){
        ui->f11InitalMode640x400RadioButton->setChecked(true);
        ui->f11InitialModeWithBorderCheckBox->setChecked(true);
    } else if (zoom.compare("640x400")==0){
        ui->f11InitalMode640x400RadioButton->setChecked(true);
    } else if (zoom.compare("full")==0){
        ui->f11InitalModeFullRadioButton->setChecked(true);
        ui->f11InitialModeWithBorderCheckBox->setDisabled(true);
    } else {
        ui->f11InitalModeAutoRadioButton->setChecked(true);
        ui->f11InitialModeWithBorderCheckBox->setDisabled(true);
    }

    //VIDEO FORMAT
    string video_format=graphicsConfiguration.getVideoFormatString();
    if (video_format.compare("rgba")==0){
        ui->videoFormatRGBARadioButton->setChecked(true);
    } else {
        ui->videoFormatBGRARadioButton->setChecked(true);
    }

    //VIDEO TEXTURE FORMAT
    string video_texture_format=graphicsConfiguration.getTextureFormatString();
    if (video_texture_format.compare("rgba8")==0){
        ui->textureFormatModeRGBA8RadioButton->setChecked(true);
    } else if (video_texture_format.compare("rgba")==0){
        ui->textureFormatModeRGBARadioButton->setChecked(true);
    } else if (video_texture_format.compare("rgb8")==0){
        ui->textureFormatModeRGB8RadioButton->setChecked(true);
    } else {
        ui->textureFormatModeRGBRadioButton->setChecked(true);
    }

    //SCANLINES SLIDERS
    string scanlines_dark=graphicsConfiguration.getScanlinesDarkString();
    ui->scanlinesDarkDisplayLabel->setText(QString::fromStdString(scanlines_dark+"%"));
    ui->scanlinesDarkHorizontalSlider->setValue(strToInt(scanlines_dark));

    string scanlines_light=graphicsConfiguration.getScanlinesLightString();
    ui->scanlinesLightDisplayLabel->setText(QString::fromStdString(scanlines_light+"%"));
    ui->scanlinesLightHorizontalSlider->setValue(strToInt(scanlines_light));

    //SHADER
    string shader=graphicsConfiguration.getShaderString();
    if(ui->shaderComboBox->findText(QString::fromStdString(shader),Qt::MatchExactly)!=-1){
        ui->shaderComboBox->setCurrentIndex(ui->shaderComboBox->findText(QString::fromStdString(shader),Qt::MatchExactly));
    } else {ui->shaderComboBox->setCurrentIndex(0); }

    //VIDEO SYNC
    string video_sync_type=graphicsConfiguration.getVideoSyncString();
    if(ui->videoSyncComboBox->findText(QString::fromStdString(video_sync_type),Qt::MatchExactly)!=-1){
        ui->videoSyncComboBox->setCurrentIndex(ui->videoSyncComboBox->findText(QString::fromStdString(video_sync_type),Qt::MatchExactly));
    } else {ui->videoSyncComboBox->setCurrentIndex(0); }

    //VIDEO SYNC METHOD
    string video_sync_method=graphicsConfiguration.getVideoSyncString();
    if(ui->videoSynkMethodeComboBox->findText(QString::fromStdString(video_sync_method),Qt::MatchExactly)!=-1){
        ui->videoSynkMethodeComboBox->setCurrentIndex(ui->videoSynkMethodeComboBox->findText(QString::fromStdString(video_sync_method),Qt::MatchExactly));
    } else {ui->videoSynkMethodeComboBox->setCurrentIndex(0); }

    //VIEWPORT
    QStringList viewportList = QString::fromStdString(graphicsConfiguration.getViewportString()).split(" ");
    if(viewportList.count()!=9){
        return;
    }
    ui->viewportIn1LineEdit->setText(viewportList.at(0));
    ui->viewportIn2LineEdit->setText(viewportList.at(1));
    ui->viewportIn3LineEdit->setText(viewportList.at(2));
    ui->viewportIn4LineEdit->setText(viewportList.at(3));
    ui->viewportOut1LineEdit->setText(viewportList.at(5));
    ui->viewportOut2LineEdit->setText(viewportList.at(6));
    ui->viewportOut3LineEdit->setText(viewportList.at(7));
    ui->viewportOut4LineEdit->setText(viewportList.at(8));

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //INPUT GRAB
    string input_grab=miscConfiguration.getInputGrabString();
    if(input_grab.compare("0")==0){
        ui->grabMouseCheckBox->setChecked(false);
    } else {
        ui->grabMouseCheckBox->setChecked(true);
    }

    //AUTO INPUT GRAB
    string automatic_input_grab=miscConfiguration.getAutomaticInputGrabString();
    if(automatic_input_grab.compare("0")==0){
        ui->grabMouseAutoCheckBox->setChecked(false);
    } else {
        ui->grabMouseAutoCheckBox->setChecked(true);
    }

    //BSD SOCKET
    string bsdsocket_library=miscConfiguration.getBsdSocketLibraryString();
    if(bsdsocket_library.compare("1")==0){
        ui->useBSDCheckBox->setChecked(true);
    } else {
        ui->useBSDCheckBox->setChecked(false);
    }

    //AUDIO BUFFER
    string audio_buffer_target_bytes=miscConfiguration.getAudioBufferString();
    ui->audioBufferLineEdit->setText(QString::fromStdString(audio_buffer_target_bytes));

    //MOUSE SPEED
    string mouse_speed=miscConfiguration.getMouseSpeedString();
    ui->mouseSpeedLineEdit->setText(QString::fromStdString(mouse_speed));

    //TITLE
    string title=miscConfiguration.getTitleString();
    ui->menuTitleLineEdit->setText(QString::fromStdString(title));

    //SUBTITLE
    string sub_title=miscConfiguration.getSubTitleString();
    ui->menuSubtitleLineEdit->setText(QString::fromStdString(sub_title));

    //NETPLAY
    string netplay_server=miscConfiguration.getNetPlayServerString();
    ui->serverIPLineEdit->setText(QString::fromStdString(netplay_server));

    string netplay_port=miscConfiguration.getNetPlayPortString();
    ui->serverPortLineEdit->setText(QString::fromStdString(netplay_port));

    string netplay_tag=miscConfiguration.getNetPlayTagString();
    ui->playerUsernameLineEdit->setText(QString::fromStdString(netplay_tag));

    string netplay_password=miscConfiguration.getNetPlayTagString();
    ui->playerPasswordLineEdit->setText(QString::fromStdString(netplay_password));

    //ALTERNATIVE DIRs
    string base_dir=miscConfiguration.getBaseDirString();
    ui->alternativeBaseDirLineEdit->setText(QString::fromStdString(base_dir));

    string kickstarts_dir=miscConfiguration.getKickstartsDirString();
    ui->alternativeKickstartDirLineEdit->setText(QString::fromStdString(kickstarts_dir));

    string save_states_dir=miscConfiguration.getSaveStatesDirString();
    ui->alternativeSaveStatesDirLineEdit->setText(QString::fromStdString(save_states_dir));

    string floppy_overlays_dir=miscConfiguration.getFloppyOverlaysDirString();
    ui->alternativeFloppyOverlaysDirLineEdit->setText(QString::fromStdString(floppy_overlays_dir));

    string flash_memory_dir=miscConfiguration.getFlashMemoryDirString();
    ui->alternativeFlashMemoryLineDirEdit->setText(QString::fromStdString(flash_memory_dir));

    string controllers_dir=miscConfiguration.getControllersDirString();
    ui->alternativeControllersDirLineEdit->setText(QString::fromStdString(controllers_dir));

    string logs_dir=miscConfiguration.getLogsDirString();
    ui->alternativeLogsDirLineEdit->setText(QString::fromStdString(logs_dir));

    string hard_drives_dir=miscConfiguration.getHardDrivesDirString();
    ui->alternativeHardDrivesDirLineEdit->setText(QString::fromStdString(hard_drives_dir));

    string cdroms_dir=miscConfiguration.getCDRomsDirString();
    ui->alternativeCdromsDirLineEdit->setText(QString::fromStdString(cdroms_dir));

    string floppies_dir=miscConfiguration.getFloppiesDirString();
    ui->alternativeFloppiesDirLineEdit->setText(QString::fromStdString(floppies_dir));

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //THEME
    string theme=themeConfiguration.getThemeString();
    ui->themeFolderLineEdit->setText(QString::fromStdString(theme));

    //THEME OVERLAY IMAGE
    string theme_overlay_image=themeConfiguration.getOverlayImageString();
    ui->themeOverlayImageLineEdit->setText(QString::fromStdString(theme_overlay_image));

    string theme_fade_color=themeConfiguration.getFadeColorString();
    ui->fadeColorPushButton->setText(QString::fromStdString(theme_fade_color));
    ui->fadeColorPushButton->setStyleSheet(QString("background-color: ").append(theme_fade_color.c_str()));

    string theme_wall_color_1=themeConfiguration.getWallColor1String();
    ui->wallColor1PushButton->setText(QString::fromStdString(theme_wall_color_1));
    ui->wallColor1PushButton->setStyleSheet(QString("background-color: ").append(theme_wall_color_1.c_str()));

    string theme_wall_color_2=themeConfiguration.getWallColor2String();
    ui->wallColor2PushButton->setText(QString::fromStdString(theme_wall_color_2));
    ui->wallColor2PushButton->setStyleSheet(QString("background-color: ").append(theme_wall_color_2.c_str()));

    string theme_floor_color_1=themeConfiguration.getFloorColor1String();
    ui->floorColor1PushButton->setText(QString::fromStdString(theme_floor_color_1));
    ui->floorColor1PushButton->setStyleSheet(QString("background-color: ").append(theme_floor_color_1.c_str()));

    string theme_floor_color_2=themeConfiguration.getFloorColor2String();
    ui->floorColor2PushButton->setText(QString::fromStdString(theme_floor_color_2));
    ui->floorColor2PushButton->setStyleSheet(QString("background-color: ").append(theme_floor_color_2.c_str()));

    string theme_heading_color=themeConfiguration.getHeadingColorString();
    ui->headColorPushButton->setText(QString::fromStdString(theme_heading_color));
    ui->headColorPushButton->setStyleSheet(QString("background-color: ").append(theme_heading_color.c_str()));

    //CUSTOM INPUT MAPPING
    ui->customInputMappingListWidget->clear();
    if (inputConfiguration.getCustomInputMappingSize()>0){
        for(int i=0;i<inputConfiguration.getCustomInputMappingSize();i++){
            ui->customInputMappingListWidget->addItem(QString::fromStdString(inputConfiguration.getCustomInputMappingAt(i)));
        }
    }

    //JOYSTICK PORT 0
    string joystick_port_0=inputConfiguration.getJoystickPort0String();
    ui->joystickPort0CustomizePushButton->setDisabled(true);
    ui->joystickPort0ModelComboBox->setDisabled(true);
    if(ui->joystickPort0ModelComboBox->findText(QString::fromStdString(joystick_port_0),Qt::MatchExactly)!=-1){
        ui->joystickPort0ModelComboBox->setCurrentIndex(ui->joystickPort0ModelComboBox->findText(QString::fromStdString(joystick_port_0),Qt::MatchExactly));
        ui->joystickPort0ModelComboBox->setDisabled(false);
        ui->joystickPort0JoystickRadioButton->setChecked(true);
    } else if(joystick_port_0.compare("mouse")==0){
        ui->joystickPort0MouseRadioButton->setChecked(true);
    } else if(joystick_port_0.compare("keyboard")==0){
        ui->joystickPort0KeyboardRadioButton->setChecked(true);
    } else if(joystick_port_0.compare("none")==0){
        ui->joystickPort0NothingRadioButton->setChecked(true);
    } else if(joystick_port_0.compare("")!=0){
        ui->joystickPort0CustomizePushButton->setDisabled(false);
        ui->joystickPort0CustomJoystickRadioButton->setChecked(true);
    }

    //JOYSTICK PORT 1
    string joystick_port_1=inputConfiguration.getJoystickPort1String();
    ui->joystickPort1CusomizePushButton->setDisabled(true);
    ui->joystickPort1ModelComboBox->setDisabled(true);
    if(ui->joystickPort1ModelComboBox->findText(QString::fromStdString(joystick_port_1),Qt::MatchExactly)!=-1){
        ui->joystickPort1ModelComboBox->setCurrentIndex(ui->joystickPort1ModelComboBox->findText(QString::fromStdString(joystick_port_1),Qt::MatchExactly));
        ui->joystickPort1ModelComboBox->setDisabled(false);
        ui->joystickPort1JoystickRadioButton->setChecked(true);
    } else if(joystick_port_1.compare("mouse")==0){
        ui->joystickPort1MouseRadioButton->setChecked(true);
    } else if(joystick_port_1.compare("keyboard")==0){
        ui->joystickPort1KeyboardRadioButton->setChecked(true);
    } else if(joystick_port_1.compare("none")==0){
        ui->joystickPort1NothingRadioButton->setChecked(true);
    } else if(joystick_port_1.compare("")!=0){
        ui->joystickPort1CusomizePushButton->setDisabled(false);
        ui->joystickPort1CustomJoystickRadioButton->setChecked(true);
    }

    //JOYSTICK PORT 2
    string joystick_port_2=inputConfiguration.getJoystickPort2String();
    ui->joystickPort2CustomizePushButton->setDisabled(true);
    ui->joystickPort2ModelComboBox->setDisabled(true);
    if(ui->joystickPort2ModelComboBox->findText(QString::fromStdString(joystick_port_2),Qt::MatchExactly)!=-1){
        ui->joystickPort2ModelComboBox->setCurrentIndex(ui->joystickPort2ModelComboBox->findText(QString::fromStdString(joystick_port_2),Qt::MatchExactly));
        ui->joystickPort2ModelComboBox->setDisabled(false);
        ui->joystickPort2JoystickRadioButton->setChecked(true);
    } else if(joystick_port_2.compare("mouse")==0){
        ui->joystickPort2MouseRadioButton->setChecked(true);
    } else if(joystick_port_2.compare("keyboard")==0){
        ui->joystickPort2KeyboardRadioButton->setChecked(true);
    } else if(joystick_port_2.compare("none")==0){
        ui->joystickPort2NothingRadioButton->setChecked(true);
    } else if(joystick_port_2.compare("")!=0){
        ui->joystickPort2CustomizePushButton->setDisabled(false);
        ui->joystickPort2CustomJoystickRadioButton->setChecked(true);
    }

    //JOYSTICK PORT 3
    string joystick_port_3=inputConfiguration.getJoystickPort3String();
    ui->joystickPort3CustomizePushButton->setDisabled(true);
    ui->joystickPort3ModelComboBox->setDisabled(true);
    if(ui->joystickPort3ModelComboBox->findText(QString::fromStdString(joystick_port_3),Qt::MatchExactly)!=-1){
        ui->joystickPort3ModelComboBox->setCurrentIndex(ui->joystickPort3ModelComboBox->findText(QString::fromStdString(joystick_port_3),Qt::MatchExactly));
        ui->joystickPort3ModelComboBox->setDisabled(false);
        ui->joystickPort3JoystickRadioButton->setChecked(true);
    } else if(joystick_port_3.compare("mouse")==0){
        ui->joystickPort3MouseRadioButton->setChecked(true);
    } else if(joystick_port_3.compare("keyboard")==0){
        ui->joystickPort3KeyboardRadioButton->setChecked(true);
    } else if(joystick_port_3.compare("none")==0){
        ui->joystickPort3NothingRadioButton->setChecked(true);
    } else if(joystick_port_3.compare("")!=0){
        ui->joystickPort3CustomizePushButton->setDisabled(false);
        ui->joystickPort3CustomJoystickRadioButton->setChecked(true);
    }

}

bool Amiga::isExistingParameter(string parameterName){
    return (chipsetConfiguration.hasParameter(parameterName)||ramConfiguration.hasParameter(parameterName)||
            floppyConfiguration.hasParameter(parameterName)||cdromConfiguration.hasParameter(parameterName)||
            hardDiskConfiguration.hasParameter(parameterName)||inputConfiguration.hasParameter(parameterName)||
            graphicsConfiguration.hasParameter(parameterName)||themeConfiguration.hasParameter(parameterName)||
            miscConfiguration.hasParameter(parameterName));
}

void Amiga::on_loadConfigToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Config file *.fs-uae (*.fs-uae)"));
    if (fileName.compare("")==0) {return; }

    //devo resettare tutte le impostazioni a default perchè nel file i valori di defult non sono esplicitamente salvati
    //quindi rischierei di vedere i valori dell'ultima config

    loadDefaultValues();

    //poi leggo riga per riga, aggiorno la configurazione interna e aggiorno i componenti

    string errorMessage;
    string line;
    ifstream myfile(fileName.toStdString().c_str());
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            getline (myfile,line);
            //int separatorPosition=line.find_first_of(" = ");
            int separatorPosition=line.find(" = ");
            string parameterName=line.substr(0,separatorPosition);
            if(line.compare("")!=0 && line.compare("[config]")!=0 &&!isExistingParameter(parameterName)){
                errorMessage.append("-Line \""+line+"\" has an invalid parameter name\n");
            }
            parseLine(line);
        }
        myfile.close();
    }

    if (errorMessage.compare("")!=0){
        showAlert(errorMessage);
    }


    checkConfigurationConsistency();// --> devo eliminare le configurazioni proibite che potrebbero essere venute fuori dal caricamento di un file manomeso

    //lo devo fare per ogni configuration area
    updateGraphicsFromInternalConfiguration();
}

void Amiga::loadDefaultValues(){
    ui->joystickPort0ModelComboBox->setCurrentIndex(0);
    ui->joystickPort1ModelComboBox->setCurrentIndex(0);
    ui->joystickPort2ModelComboBox->setCurrentIndex(0);
    ui->joystickPort3ModelComboBox->setCurrentIndex(0);

    chipsetConfiguration.setToDefaultConfiguration();
    ramConfiguration.setToDefaultConfiguration();
    floppyConfiguration.setToDefaultConfiguration();
    cdromConfiguration.setToDefaultConfiguration();
    hardDiskConfiguration.setToDefaultConfiguration();
    graphicsConfiguration.setToDefaultConfiguration();
    themeConfiguration.setToDefaultConfiguration();
    miscConfiguration.setToDefaultConfiguration();
    inputConfiguration.setToDefaultConfiguration();

    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_loadDefaultValuesToolButton_clicked()
{
    loadDefaultValues();
}

void Amiga::on_runConfigButton_clicked()
{
    checkConfigurationConsistency();// --> devo eliminare le configurazioni proibite che potrebbero essere venute fuori dal caricamento di un file manomeso

    updateGraphicsFromInternalConfiguration();

    saveConfigInFile(".current.fs-uae");

    int returnValue=system("fs-uae .current.fs-uae");
    if (returnValue!=0)
    {
        QMessageBox::about(this, tr("Error"),tr("Ops...something went wrong :-("));
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Amiga::on_kickstartFileToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Image ADF/ROM(*.adf *.rom)"));
    ui->kickstartFileLineEdit->setText(fileName);
    chipsetConfiguration.setParameter("kickstart_file",fileName.toStdString());
}
void Amiga::on_kickstartExtFileToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Image ROM(*.rom)"));
    ui->kickstartExtFileLineEdit->setText(fileName);
    chipsetConfiguration.setParameter("kickstart_ext_file",fileName.toStdString());
}

void Amiga::on_amigaModelComboBox_currentIndexChanged(const QString &arg1)
{
    chipsetConfiguration.setParameter("amiga_model",arg1.toStdString());
    updateGraphicsFromInternalConfiguration();
}
void Amiga::on_accuracyLeastRadio_clicked()
{
    chipsetConfiguration.setParameter("accuracy","-1");
}
void Amiga::on_accuracyNormalRadio_clicked()
{
    chipsetConfiguration.setParameter("accuracy","0");
}
void Amiga::on_accuracyMostadio_clicked()
{
    chipsetConfiguration.setParameter("accuracy","1");
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

void Amiga::setFastMemoryDisabled(bool state){
    ui->fastMem1MbRadio->setDisabled(state);
    ui->fastMem2MbRadio->setDisabled(state);
    ui->fastMem4MbRadio->setDisabled(state);
    ui->fastMem8MbRadio->setDisabled(state);
    ui->fastMemLabel->setDisabled(state);
    ui->fastMemNoneRadio->setDisabled(state);
}

void Amiga::setZorroIIIMemoryDisabled(bool state){
    ui->z3MemLabel->setDisabled(state);
    ui->z3Mem128MbRadio->setDisabled(state);
    ui->z3Mem16MbRadio->setDisabled(state);
    ui->z3Mem1MbRadio->setDisabled(state);
    ui->z3Mem256MbRadio->setDisabled(state);
    ui->z3Mem2MbRadio->setDisabled(state);
    ui->z3Mem32MbRadio->setDisabled(state);
    ui->z3Mem4MbRadio->setDisabled(state);
    ui->z3Mem64MbRadio->setDisabled(state);
    ui->z3Mem8MbRadio->setDisabled(state);
    ui->z3MemNoneRadio->setDisabled(state);
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

void Amiga::on_actionAmiga_triggered()
{
    ui->mainTabWidget->setCurrentIndex(8);
}

void Amiga::on_actionSummary_triggered()
{
    char *username=getenv("USER");
    string index="file:///home/"+string(username)+"/.FS-UAE/html/index.html";
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
    string stringvalue=intToStr(value);

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
        string stringvalue=intToStr(ui->floppyDriveVolumeSlider->value());
        ui->floppyDriveVolumeDisplayLabel->setText(QString::fromStdString(stringvalue));
        ui->floppyDriveVolumeSlider->setEnabled(true);
        floppyConfiguration.setParameter("floppy_drive_volume",stringvalue);
    }
}

void Amiga::on_floppyDriveSpeedSlider_valueChanged(int position)
{
    //0<=position<=12
    string positionString=intToStr(position);
    string stringvalue=intToStr(position*100);
    floppyConfiguration.setParameter("floppy_drive_speed",stringvalue);
    string displayString;
    if (position==0){
        displayString="TURBO";
    } else{
        displayString=positionString+"X";
    }
    ui->floppyDriveSpeedDisplayLabel->setText(QString::fromStdString(displayString));
}

void Amiga::on_cdromDrive0ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("CD Image CUE/BIN/ISO(*.cue *.bin *.iso)"));
    ui->cdromDrive0LineEdit->setText(fileName);
    cdromConfiguration.setParameter("cdrom_drive_0",fileName.toStdString());
}

void Amiga::on_cdromSwappingImagesAddPushButton_clicked()
{
    if (ui->cdromSwappingImagesListWidget->count()==20){
        QMessageBox::about(this, tr("Error"),tr("You can select at most 20 CDRoms"));
        return;}
    QStringList fileNames=QFileDialog::getOpenFileNames(this, tr("Open file"), QDir::homePath(), tr("CD Image CUE/BIN/ISO(*.cue *.bin *.iso)"));

    if (fileNames.count()==0){
        //hai premuto annulla
        return;}

    if (fileNames.count()+ui->cdromSwappingImagesListWidget->count()>20){
        QMessageBox::about(this, tr("Error"),tr("You can select at most 20 CDRoms"));
        return;}

    for(int i=0;i<fileNames.count();i++){
        //aggiorno la lista interna
        cdromConfiguration.pushBackCDRomImage(fileNames.at(i).toStdString());
    }
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_cdromSwappingImagesRemovePushButton_clicked()
{
    //devo rimuovere i selezionati dalla lista interna
    QItemSelectionModel *selection = ui->cdromSwappingImagesListWidget->selectionModel();
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
        cdromConfiguration.erasCDRomImageAt(indexList[x]);
    }

    //svuoto lista grafica
    ui->cdromSwappingImagesListWidget->clear();

    //aggiorno la grafica
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_hardDrive0ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive0LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_0",fileName.toStdString());
}

void Amiga::on_hardDrive0FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive0LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_0",dir.toStdString());
}

void Amiga::on_hardDrive1ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive1LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_1",fileName.toStdString());
}

void Amiga::on_hardDrive1FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive1LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_1",dir.toStdString());
}

void Amiga::on_hardDrive2ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive2LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_2",fileName.toStdString());
}

void Amiga::on_hardDrive2FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive2LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_2",dir.toStdString());
}

void Amiga::on_hardDrive3ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive3LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_3",fileName.toStdString());
}

void Amiga::on_hardDrive3FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive3LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_3",dir.toStdString());
}

void Amiga::on_hardDrive4ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive4LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_4",fileName.toStdString());
}

void Amiga::on_hardDrive4FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive4LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_4",dir.toStdString());
}

void Amiga::on_hardDrive5ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive5LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_5",fileName.toStdString());
}

void Amiga::on_hardDrive5FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive5LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_5",dir.toStdString());
}

void Amiga::on_hardDrive6ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive6LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_6",fileName.toStdString());
}

void Amiga::on_hardDrive6FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive6LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_6",dir.toStdString());
}

void Amiga::on_hardDrive7ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive7LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_7",fileName.toStdString());
}

void Amiga::on_hardDrive7FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive7LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_7",dir.toStdString());
}

void Amiga::on_hardDrive8ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive8LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_8",fileName.toStdString());
}

void Amiga::on_hardDrive8FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive8LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_8",dir.toStdString());
}

void Amiga::on_hardDrive9ToolButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File adf/zip(*.adf *.zip)"));
    ui->hardDrive9LineEdit->setText(fileName);
    hardDiskConfiguration.setParameter("hard_drive_9",fileName.toStdString());
}

void Amiga::on_hardDrive9FolderToolButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->hardDrive9LineEdit->setText(dir);
    hardDiskConfiguration.setParameter("hard_drive_9",dir.toStdString());
}

void Amiga::on_hardDrive0LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_0_label",arg1.toStdString());
}

void Amiga::on_hardDrive1LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_1_label",arg1.toStdString());
}

void Amiga::on_hardDrive2LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_2_label",arg1.toStdString());
}

void Amiga::on_hardDrive3LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_3_label",arg1.toStdString());
}

void Amiga::on_hardDrive4LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_4_label",arg1.toStdString());
}

void Amiga::on_hardDrive5LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_5_label",arg1.toStdString());
}

void Amiga::on_hardDrive6LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_6_label",arg1.toStdString());
}

void Amiga::on_hardDrive7LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_7_label",arg1.toStdString());
}

void Amiga::on_hardDrive8LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_8_label",arg1.toStdString());
}

void Amiga::on_hardDrive9LabelLineEdit_textChanged(const QString &arg1)
{
    hardDiskConfiguration.setParameter("hard_drive_9_label",arg1.toStdString());
}

void Amiga::on_hardDrive0ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive0ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_0_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_0_read_only","0");
    }
}

void Amiga::on_hardDrive1ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive1ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_1_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_1_read_only","0");
    }
}

void Amiga::on_hardDrive2ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive2ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_2_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_2_read_only","0");
    }
}

void Amiga::on_hardDrive3ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive3ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_3_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_3_read_only","0");
    }
}

void Amiga::on_hardDrive4ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive4ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_4_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_4_read_only","0");
    }
}

void Amiga::on_hardDrive5ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive5ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_5_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_5_read_only","0");
    }
}

void Amiga::on_hardDrive6ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive6ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_6_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_6_read_only","0");
    }
}

void Amiga::on_hardDrive7ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive7ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_7_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_7_read_only","0");
    }
}

void Amiga::on_hardDrive8ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive8ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_8_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_8_read_only","0");
    }
}

void Amiga::on_hardDrive9ReadOnlyCheckBox_clicked()
{
    if(ui->hardDrive9ReadOnlyCheckBox->isChecked()){
        hardDiskConfiguration.setParameter("hard_drive_9_read_only","1");
    } else {
        hardDiskConfiguration.setParameter("hard_drive_9_read_only","0");
    }
}

void Amiga::on_displaySettingsStartFullscreenRadioButton_clicked()
{
    if(ui->displaySettingsStartFullscreenRadioButton->isChecked()){
        graphicsConfiguration.setParameter("fullscreen","1");
    } else {
        graphicsConfiguration.setParameter("fullscreen","0");
    }
}

void Amiga::on_displaySettingsResizableRadioButton_clicked()
{
    if(ui->displaySettingsResizableRadioButton->isChecked()){
        graphicsConfiguration.setParameter("window_resizable","1");
    } else {
        graphicsConfiguration.setParameter("window_resizable","0");
    }
}

void Amiga::on_displaySettingsKeepAspectRatioRadioButton_clicked()
{
    if(ui->displaySettingsKeepAspectRatioRadioButton->isChecked()){
        graphicsConfiguration.setParameter("keep_aspect","1");
    } else {
        graphicsConfiguration.setParameter("keep_aspect","0");
    }
}

void Amiga::on_scanlinesRadioButton_clicked()
{
    if(ui->scanlinesRadioButton->isChecked()){
        graphicsConfiguration.setParameter("scanlines","1");
    } else {
        graphicsConfiguration.setParameter("scanlines","0");
    }
}

void Amiga::on_scanlinesRTGRadioButton_clicked()
{
    if(ui->scanlinesRTGRadioButton->isChecked()){
        graphicsConfiguration.setParameter("rtg_scanlines","1");
    } else {
        graphicsConfiguration.setParameter("rtg_scanlines","0");
    }
}

void Amiga::on_lowResolutionRadioButton_clicked()
{
    if(ui->lowResolutionRadioButton->isChecked()){
        graphicsConfiguration.setParameter("low_resolution","1");
    } else {
        graphicsConfiguration.setParameter("low_resolution","0");
    }
}

void Amiga::on_lineDoublingRadioButton_clicked()
{
    if(ui->lineDoublingRadioButton->isChecked()){
        graphicsConfiguration.setParameter("line_doubling","1");
    } else {
        graphicsConfiguration.setParameter("line_doubling","0");
    }
}

void Amiga::on_fullscreenResolutionXSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("fullscreen_width",arg1.toStdString());
}


void Amiga::on_fullscreenResolutionYSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("fullscreen_height",arg1.toStdString());
}

void Amiga::on_windowResolutionXSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("window_width",arg1.toStdString());
}

void Amiga::on_windowResolutionYSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("window_height",arg1.toStdString());
}

void Amiga::on_scaleXDoubleSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("scale_x",arg1.toStdString());
}


void Amiga::on_scaleYDoubleSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("scale_y",arg1.toStdString());
}

void Amiga::on_alignXdoubleSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("align_x",arg1.toStdString());
}

void Amiga::on_alignYDoubleSpinBox_valueChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("align_y",arg1.toStdString());
}

void Amiga::on_scanlinesDarkHorizontalSlider_valueChanged(int position)
{
    string positionString=intToStr(position);
    graphicsConfiguration.setParameter("scanlines_dark",positionString);
    ui->scanlinesDarkDisplayLabel->setText(QString::fromStdString(positionString+"%"));
}

void Amiga::on_scanlinesLightHorizontalSlider_valueChanged(int position)
{
    string positionString=intToStr(position);
    graphicsConfiguration.setParameter("scanlines_light",positionString);
    ui->scanlinesLightDisplayLabel->setText(QString::fromStdString(positionString+"%"));
}

void Amiga::on_fullSceneAntiAliasingOffRadioButton_clicked()
{
    graphicsConfiguration.setParameter("fsaa","0");
}

void Amiga::on_fullSceneAntiAliasing2xRadioButton_clicked()
{
    graphicsConfiguration.setParameter("fsaa","2");
}

void Amiga::on_fullSceneAntiAliasing4xRadioButton_clicked()
{
    graphicsConfiguration.setParameter("fsaa","4");
}

void Amiga::on_fullSceneAntiAliasing8xRadioButton_clicked()
{
    graphicsConfiguration.setParameter("fsaa","8");
}

void Amiga::on_textureFilterLinearRadioButton_clicked()
{
    graphicsConfiguration.setParameter("texture_filter","linear");
}

void Amiga::on_textureFilterNearestRadioButton_clicked()
{
    graphicsConfiguration.setParameter("texture_filter","nearest");
}

void Amiga::on_f11InitalModeAutoRadioButton_clicked()
{
    ui->f11InitialModeWithBorderCheckBox->setDisabled(true);
    ui->f11InitialModeWithBorderCheckBox->setChecked(false);
    graphicsConfiguration.setParameter("zoom","auto");
}

void Amiga::on_f11InitalModeFullRadioButton_clicked()
{
    ui->f11InitialModeWithBorderCheckBox->setDisabled(true);
    ui->f11InitialModeWithBorderCheckBox->setChecked(false);
    graphicsConfiguration.setParameter("zoom","full");
}

void Amiga::on_f11InitalMode640x400RadioButton_clicked()
{
    ui->f11InitialModeWithBorderCheckBox->setDisabled(false);
    if (ui->f11InitialModeWithBorderCheckBox->isChecked()){
        graphicsConfiguration.setParameter("zoom","640x400+border");
    } else {
        graphicsConfiguration.setParameter("zoom","640x400");
    }
}

void Amiga::on_f11InitalMode640x480RadioButton_clicked()
{
    ui->f11InitialModeWithBorderCheckBox->setDisabled(false);
    if (ui->f11InitialModeWithBorderCheckBox->isChecked()){
        graphicsConfiguration.setParameter("zoom","640x480+border");
    } else {
        graphicsConfiguration.setParameter("zoom","640x480");
    }
}

void Amiga::on_f11InitalMode640x512RadioButton_clicked()
{
    ui->f11InitialModeWithBorderCheckBox->setDisabled(false);
    if (ui->f11InitialModeWithBorderCheckBox->isChecked()){
        graphicsConfiguration.setParameter("zoom","640x512+border");
    } else {
        graphicsConfiguration.setParameter("zoom","640x512");
    }
}

void Amiga::on_f11InitialModeWithBorderCheckBox_clicked()
{
    if (ui->f11InitialModeWithBorderCheckBox->isChecked()){
        if (ui->f11InitalMode640x400RadioButton->isChecked()){
            graphicsConfiguration.setParameter("zoom","640x400+border");
        } else if (ui->f11InitalMode640x480RadioButton->isChecked()){
            graphicsConfiguration.setParameter("zoom","640x480+border");
        } else if (ui->f11InitalMode640x512RadioButton->isChecked()){
            graphicsConfiguration.setParameter("zoom","640x512+border");
        }
    } else {
        if (ui->f11InitalMode640x400RadioButton->isChecked()){
            graphicsConfiguration.setParameter("zoom","640x400");
        } else if (ui->f11InitalMode640x480RadioButton->isChecked()){
            graphicsConfiguration.setParameter("zoom","640x480");
        } else if (ui->f11InitalMode640x512RadioButton->isChecked()){
            graphicsConfiguration.setParameter("zoom","640x512");
        }
    }
}

void Amiga::on_videoFormatBGRARadioButton_clicked()
{
    graphicsConfiguration.setParameter("video_format","bgra");
}

void Amiga::on_videoFormatRGBARadioButton_clicked()
{
    graphicsConfiguration.setParameter("video_format","rgba");
}


void Amiga::on_textureFormatModeRGBRadioButton_clicked()
{
    graphicsConfiguration.setParameter("texture_format","rgb");
}

void Amiga::on_textureFormatModeRGB8RadioButton_clicked()
{
    graphicsConfiguration.setParameter("texture_format","rgb8");
}

void Amiga::on_textureFormatModeRGBARadioButton_clicked()
{
    graphicsConfiguration.setParameter("texture_format","rgba");
}

void Amiga::on_textureFormatModeRGBA8RadioButton_clicked()
{
    graphicsConfiguration.setParameter("texture_format","rgba8");
}

void Amiga::on_shaderComboBox_currentIndexChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("shader",arg1.toStdString());
}

void Amiga::on_videoSyncComboBox_currentIndexChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("video_sync",arg1.toStdString());
}

void Amiga::on_videoSynkMethodeComboBox_currentIndexChanged(const QString &arg1)
{
    graphicsConfiguration.setParameter("video_sync_method",arg1.toStdString());
}

// PER CAMBIARE COLORE AL BOTTONE
void Amiga::on_fadeColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->fadeColorPushButton->setText(color.name());
    ui->fadeColorPushButton->setStyleSheet(QString("background-color: ")+color.name());
    themeConfiguration.setParameter("theme_fade_color",color.name().toStdString());
}


void Amiga::on_viewportIn1LineEdit_textChanged(const QString &arg1)
{
    string viewportString=arg1.toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportIn2LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=arg1.toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportIn3LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=arg1.toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportIn4LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=arg1.toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportOut1LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=arg1.toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportOut2LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=arg1.toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportOut3LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=arg1.toStdString()+" ";
    viewportString+=ui->viewportOut4LineEdit->text().toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_viewportOut4LineEdit_textChanged(const QString &arg1)
{
    string viewportString=ui->viewportIn1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn3LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportIn4LineEdit->text().toStdString()+" ";
    viewportString+="=> ";
    viewportString+=ui->viewportOut1LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut2LineEdit->text().toStdString()+" ";
    viewportString+=ui->viewportOut3LineEdit->text().toStdString()+" ";
    viewportString+=arg1.toStdString();

    graphicsConfiguration.setParameter("viewport",viewportString);
}

void Amiga::on_alternativeBaseDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeBaseDirLineEdit->setText(dir);
    miscConfiguration.setParameter("base_dir",dir.toStdString());
}

void Amiga::on_alternativeKickstartDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeKickstartDirLineEdit->setText(dir);
    miscConfiguration.setParameter("kickstarts_dir",dir.toStdString());
}

void Amiga::on_alernativeSaveStatesDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeSaveStatesDirLineEdit->setText(dir);
    miscConfiguration.setParameter("save_states_dir",dir.toStdString());
}

void Amiga::on_alternativeFloppyOverlaysDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeFloppyOverlaysDirLineEdit->setText(dir);
    miscConfiguration.setParameter("floppy_overlays_dir",dir.toStdString());
}

void Amiga::on_alternativeFlashMemoryDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeFlashMemoryLineDirEdit->setText(dir);
    miscConfiguration.setParameter("flash_memory_dir",dir.toStdString());
}

void Amiga::on_alternativeControllersDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeControllersDirLineEdit->setText(dir);
    miscConfiguration.setParameter("controllers_dir",dir.toStdString());
}

void Amiga::on_alternativeLogsDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeLogsDirLineEdit->setText(dir);
    miscConfiguration.setParameter("logs_dir",dir.toStdString());
}

void Amiga::on_alternativeHardDrivesDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeHardDrivesDirLineEdit->setText(dir);
    miscConfiguration.setParameter("hard_drives_dir",dir.toStdString());
}

void Amiga::on_alternativeCdromsDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeCdromsDirLineEdit->setText(dir);
    miscConfiguration.setParameter("cdroms_dir",dir.toStdString());
}

void Amiga::on_alternativeFloppiesDirPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->alternativeFloppiesDirLineEdit->setText(dir);
    miscConfiguration.setParameter("floppies_dir",dir.toStdString());
}

void Amiga::on_grabMouseCheckBox_clicked()
{
    if(ui->grabMouseCheckBox->isChecked()){
        miscConfiguration.setParameter("input_grab","1");
    } else {
        miscConfiguration.setParameter("input_grab","0");
    }
}

void Amiga::on_grabMouseAutoCheckBox_clicked()
{
    if(ui->grabMouseAutoCheckBox->isChecked()){
        miscConfiguration.setParameter("automatic_input_grab","1");
    } else {
        miscConfiguration.setParameter("automatic_input_grab","0");
    }
}

void Amiga::on_useBSDCheckBox_clicked()
{
    if(ui->useBSDCheckBox->isChecked()){
        miscConfiguration.setParameter("bsdsocket_library","1");
    } else {
        miscConfiguration.setParameter("bsdsocket_library","0");
    }
}

void Amiga::on_audioBufferLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("audio_buffer_target_bytes",arg1.toStdString());
}

void Amiga::on_menuTitleLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("title",arg1.toStdString());
}

void Amiga::on_menuSubtitleLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("sub_title",arg1.toStdString());
}

void Amiga::on_serverIPLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("netplay_server",arg1.toStdString());
}

void Amiga::on_serverPortLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("netplay_port",arg1.toStdString());
}

void Amiga::on_playerUsernameLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("netplay_tag",arg1.toStdString());
}

void Amiga::on_playerPasswordLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("netplay_password",arg1.toStdString());
}

void Amiga::on_wallColor1PushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->wallColor1PushButton->setText(color.name());
    ui->wallColor1PushButton->setStyleSheet(QString("background-color: ")+color.name());
    themeConfiguration.setParameter("theme_wall_color_1",color.name().toStdString());
}

void Amiga::on_wallColor2PushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->wallColor2PushButton->setText(color.name());
    ui->wallColor2PushButton->setStyleSheet(QString("background-color: ")+color.name());
    themeConfiguration.setParameter("theme_wall_color_2",color.name().toStdString());
}

void Amiga::on_floorColor1PushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->floorColor1PushButton->setText(color.name());
    ui->floorColor1PushButton->setStyleSheet(QString("background-color: ")+color.name());
    themeConfiguration.setParameter("theme_floor_color_1",color.name().toStdString());
}

void Amiga::on_floorColor2PushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->floorColor2PushButton->setText(color.name());
    ui->floorColor2PushButton->setStyleSheet(QString("background-color: ")+color.name());
    themeConfiguration.setParameter("theme_floor_color_2",color.name().toStdString());
}

void Amiga::on_headColorPushButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    ui->headColorPushButton->setText(color.name());
    ui->headColorPushButton->setStyleSheet(QString("background-color: ")+color.name());
    themeConfiguration.setParameter("theme_heading_color",color.name().toStdString());
}

void Amiga::on_themeOverlayImagerPushButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("File png(*.png)"));
    ui->themeOverlayImageLineEdit->setText(fileName);
    themeConfiguration.setParameter("theme_overlay_image",fileName.toStdString());
}

void Amiga::on_themeFolderPushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),QDir::homePath(), QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->themeFolderLineEdit->setText(dir);
    themeConfiguration.setParameter("theme",dir.toStdString());
}

void Amiga::on_mouseSpeedLineEdit_textChanged(const QString &arg1)
{
    miscConfiguration.setParameter("uae_input.mouse_speed",arg1.toStdString());
}

void Amiga::customJoystick0Slot(QString s){
    inputConfiguration.setParameter("joystick_port_0",s.toStdString());
}
void Amiga::customJoystick1Slot(QString s){
    inputConfiguration.setParameter("joystick_port_1",s.toStdString());
}
void Amiga::customJoystick2Slot(QString s){
    inputConfiguration.setParameter("joystick_port_2",s.toStdString());
}
void Amiga::customJoystick3Slot(QString s){
    inputConfiguration.setParameter("joystick_port_3",s.toStdString());
}

QString getAmigaKeyboardKeysFromKey(int key){
    /*
    To map an action, you add a line like this to your configuration file:
    devicename_eventname = actionname
    Here is a specific example, mapping the keyboard key q to the fire button on the primary Amiga joystick (joy_1 is the joystick in joystick port 1):
    keyboard_key_q = action_joy_1_fire_button
    */
    switch(key)
    {
    case Qt::Key_Backspace:
        return QString("keyboard_key_backspace");
        break;
    case Qt::Key_Tab:
        return QString("keyboard_key_tab");
        break;
    case Qt::Key_Clear:
        return QString("keyboard_key_clear");
        break;
    case Qt::Key_Return:
        return QString("keyboard_key_return");
        break;
    case Qt::Key_Pause:
        return QString("keyboard_key_pause");
        break;
    case Qt::Key_Escape:
        return QString("keyboard_key_escape");
        break;
    case Qt::Key_Space:
        return QString("keyboard_key_space");
        break;
    case Qt::Key_Exclam:
        return QString("keyboard_key_exclaim");
        break;
    case Qt::Key_QuoteDbl:
        return QString("keyboard_key_quotedbl");
        break;
    case Qt::Key_QuoteLeft:
        return QString("keyboard_key_quote");
        break;
    case Qt::Key_ParenLeft:
        return QString("keyboard_key_leftparen");
        break;
    case Qt::Key_ParenRight:
        return QString("keyboard_key_rightparen");
        break;
    case Qt::Key_Asterisk:
        return QString("keyboard_key_asterisk");
        break;
    case Qt::Key_Plus:
        return QString("keyboard_key_plus");
        break;
    case Qt::Key_Comma:
        return QString("keyboard_key_comma");
        break;
    case Qt::Key_Minus:
        return QString("keyboard_key_minus");
        break;
    case Qt::Key_Period:
        return QString("keyboard_key_period");
        break;
    case Qt::Key_Slash:
        return QString("keyboard_key_slash");
        break;
    case Qt::Key_Ampersand:
        return QString("keyboard_key_ampersand");
        break;
    case Qt::Key_0:
        return QString("keyboard_key_0");
        break;
    case Qt::Key_1:
        return QString("keyboard_key_1");
        break;
    case Qt::Key_2:
        return QString("keyboard_key_2");
        break;
    case Qt::Key_3:
        return QString("keyboard_key_3");
        break;
    case Qt::Key_4:
        return QString("keyboard_key_4");
        break;
    case Qt::Key_5:
        return QString("keyboard_key_5");
        break;
    case Qt::Key_6:
        return QString("keyboard_key_6");
        break;
    case Qt::Key_7:
        return QString("keyboard_key_7");
        break;
    case Qt::Key_8:
        return QString("keyboard_key_8");
        break;
    case Qt::Key_9:
        return QString("keyboard_key_9");
        break;
    case Qt::Key_Colon:
        return QString("keyboard_key_colon");
        break;
    case Qt::Key_Semicolon:
        return QString("keyboard_key_semicolon");
        break;
    case Qt::Key_Less:
        return QString("keyboard_key_less");
        break;
    case Qt::Key_Equal:
        return QString("keyboard_key_equals");
        break;
    case Qt::Key_Greater:
        return QString("keyboard_key_greater");
        break;
    case Qt::Key_Question:
        return QString("keyboard_key_question");
        break;
    case Qt::Key_At:
        return QString("keyboard_key_at");
        break;
    case Qt::Key_BracketLeft:
        return QString("keyboard_key_leftbracket");
        break;
    case Qt::Key_Backslash:
        return QString("keyboard_key_backslash");
        break;
    case Qt::Key_BracketRight:
        return QString("keyboard_key_rightbracket");
        break;
    case Qt::Key_Underscore:
        return QString("keyboard_key_underscore");
        break;
    case Qt::Key_A:
        return QString("keyboard_key_a");
        break;
    case Qt::Key_B:
        return QString("keyboard_key_b");
        break;
    case Qt::Key_C:
        return QString("keyboard_key_c");
        break;
    case Qt::Key_D:
        return QString("keyboard_key_d");
        break;
    case Qt::Key_E:
        return QString("keyboard_key_e");
        break;
    case Qt::Key_F:
        return QString("keyboard_key_f");
        break;
    case Qt::Key_G:
        return QString("keyboard_key_g");
        break;
    case Qt::Key_H:
        return QString("keyboard_key_h");
        break;
    case Qt::Key_I:
        return QString("keyboard_key_i");
        break;
    case Qt::Key_J:
        return QString("keyboard_key_j");
        break;
    case Qt::Key_K:
        return QString("keyboard_key_k");
        break;
    case Qt::Key_L:
        return QString("keyboard_key_l");
        break;
    case Qt::Key_M:
        return QString("keyboard_key_m");
        break;
    case Qt::Key_N:
        return QString("keyboard_key_n");
        break;
    case Qt::Key_O:
        return QString("keyboard_key_o");
        break;
    case Qt::Key_P:
        return QString("keyboard_key_p");
        break;
    case Qt::Key_Q:
        return QString("keyboard_key_q");
        break;
    case Qt::Key_R:
        return QString("keyboard_key_r");
        break;
    case Qt::Key_S:
        return QString("keyboard_key_s");
        break;
    case Qt::Key_T:
        return QString("keyboard_key_t");
        break;
    case Qt::Key_U:
        return QString("keyboard_key_u");
        break;
    case Qt::Key_V:
        return QString("keyboard_key_v");
        break;
    case Qt::Key_W:
        return QString("keyboard_key_w");
        break;
    case Qt::Key_X:
        return QString("keyboard_key_x");
        break;
    case Qt::Key_Y:
        return QString("keyboard_key_y");
        break;
    case Qt::Key_Z:
        return QString("keyboard_key_z");
        break;
    case Qt::Key_Up:
        return QString("keyboard_key_up");
        break;
    case Qt::Key_Down:
        return QString("keyboard_key_down");
        break;
    case Qt::Key_Right:
        return QString("keyboard_key_right");
        break;
    case Qt::Key_Left:
        return QString("keyboard_key_left");
        break;
    case Qt::Key_Insert:
        return QString("keyboard_key_insert");
        break;
    case Qt::Key_Delete:
        return QString("keyboard_key_delete");
        break;
    case Qt::Key_Home:
        return QString("keyboard_key_home");
        break;
    case Qt::Key_End:
        return QString("keyboard_key_end");
        break;
    case Qt::Key_PageUp:
        return QString("keyboard_key_pageup");
        break;
    case Qt::Key_PageDown:
        return QString("keyboard_key_pagedown");
        break;
    case Qt::Key_F1:
        return QString("keyboard_key_f1");
        break;
    case Qt::Key_F2:
        return QString("keyboard_key_f2");
        break;
    case Qt::Key_F3:
        return QString("keyboard_key_f3");
        break;
    case Qt::Key_F4:
        return QString("keyboard_key_f4");
        break;
    case Qt::Key_F5:
        return QString("keyboard_key_f5");
        break;
    case Qt::Key_F6:
        return QString("keyboard_key_f6");
        break;
    case Qt::Key_F7:
        return QString("keyboard_key_f7");
        break;
    case Qt::Key_F8:
        return QString("keyboard_key_f8");
        break;
    case Qt::Key_F9:
        return QString("keyboard_key_f9");
        break;
    case Qt::Key_F10:
        return QString("keyboard_key_f10");
        break;
    case Qt::Key_F11:
        return QString("keyboard_key_f11");
        break;
    case Qt::Key_F12:
        return QString("keyboard_key_f12");
        break;
    case Qt::Key_F13:
        return QString("keyboard_key_f13");
        break;
    case Qt::Key_F14:
        return QString("keyboard_key_f14");
        break;
    case Qt::Key_F15:
        return QString("keyboard_key_f15");
        break;
    case Qt::Key_NumLock:
        return QString("keyboard_key_numlock");
        break;
    case Qt::Key_CapsLock:
        return QString("keyboard_key_capslock");
        break;
    case Qt::Key_ScrollLock:
        return QString("keyboard_key_scrollock");
        break;
    case Qt::Key_Shift:
        return QString("keyboard_key_rshift");
        break;
    case Qt::Key_Control:
        return QString("keyboard_key_rctrl");
        break;
    case Qt::Key_AltGr:
        return QString("keyboard_key_ralt");
        break;
    case Qt::Key_Alt:
        return QString("keyboard_key_lalt");
        break;
    case Qt::Key_Meta:
        return QString("keyboard_key_rmeta");
        break;
    case Qt::Key_Super_R:
        return QString("keyboard_key_rsuper");
        break;
    case Qt::Key_Super_L:
        return QString("keyboard_key_lsuper");
        break;
    case Qt::Key_Mode_switch:
        return QString("keyboard_key_mode");
        break;
    case Qt::Key_Help:
        return QString("keyboard_key_help");
        break;
    case Qt::Key_Print:
        return QString("keyboard_key_print");
        break;
    case Qt::Key_SysReq:
        return QString("keyboard_key_sysreq");
        break;
    case Qt::Key_Menu:
        return QString("keyboard_key_menu");
        break;
    case Qt::Key_PowerOff:
        return QString("keyboard_key_power");
        break;

        /*

NON POSSO DISTINGURE SHIFT DX/SX E CTRL DX/SX
keyboard_key_lshift
keyboard_key_lctrl
keyboard_key_lmeta

NON POSSO DISTINGUERE IL TASTIERINO NUMERICO
keyboard_key_kp0
keyboard_key_kp1
keyboard_key_kp2
keyboard_key_kp3
keyboard_key_kp4
keyboard_key_kp5
keyboard_key_kp6
keyboard_key_kp7
keyboard_key_kp8
keyboard_key_kp9
keyboard_key_kp_period
keyboard_key_kp_divide
keyboard_key_kp_multiply
keyboard_key_kp_minus
keyboard_key_kp_plus
keyboard_key_kp_enter
keyboard_key_kp_equals

NON LI TROVO QUESTI...
keyboard_key_caret
keyboard_key_hash
keyboard_key_dollar
keyboard_key_backquote
keyboard_key_compose
keyboard_key_break
keyboard_key_euro
keyboard_key_undo

          */
    default:
        return QString("");
    }
}

bool Amiga::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        ui->keyboardEventLineEdit->setText(getAmigaKeyboardKeysFromKey(keyEvent->key()));
        /* ui->readKeyPushButton->setText("Read Key from Keyboard");
        ui->readKeyPushButton->setStyleSheet(QString(""));*/
        return true;
    }  else
        if (event->type() == QEvent::FocusOut) {
            ui->readKeyPushButton->setText("Read Key from Keyboard");
            ui->readKeyPushButton->setStyleSheet(QString(""));
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
}

void Amiga::on_readKeyPushButton_clicked()
{
    ui->readKeyPushButton->installEventFilter(this);
    ui->readKeyPushButton->setText(". . . reading . . .");
    ui->readKeyPushButton->setStyleSheet(QString("background-color: red"));
}
void Amiga::on_customInputMappingAddPushButton_clicked()
{
    ////NON faccio alcun controllo sul fatto che potrei già aver assegnato la stessa azione o lo stesso tasto?? magari sì

    //keyboard_key_q = action_joy_1_fire_button
    if (ui->keyboardEventLineEdit->text().compare("")==0){
        QMessageBox::about(this, tr("Error"),tr("You must assign a Key Value"));
        return;}
    if (inputConfiguration.containsKeyOrAction(ui->keyboardEventLineEdit->text().toStdString())){
        QMessageBox::about(this, tr("Error"),QString("You have already assigned \""+ui->keyboardEventLineEdit->text()+"\" key."));
        return;
    }
    if (inputConfiguration.containsKeyOrAction(ui->actionsComboBox->currentText().toStdString())){
        QMessageBox::about(this, tr("Error"),QString("You have already assigned \""+ui->actionsComboBox->currentText()+"\" action."));
        return;
    }

    inputConfiguration.setParameter(ui->keyboardEventLineEdit->text().toStdString(),ui->actionsComboBox->currentText().toStdString());

    ui->keyboardEventLineEdit->setText("");
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_customInputMappingRemovePushButton_clicked()
{
    //devo rimuovere i selezionati dalla lista interna
    QItemSelectionModel *selection = ui->customInputMappingListWidget->selectionModel();
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
        inputConfiguration.eraseCustomInputMappingAt(indexList[x]);
    }

    //svuoto lista grafica
    ui->customInputMappingListWidget->clear();

    //aggiorno la grafica
    updateGraphicsFromInternalConfiguration();
}

const QString pro="Custom configurations file can be placed in the directory: Documents/FS-UAE/Controllers/<br>"
        "The name of the ini file is the system name of the controller, converted to lowercase,<br>"
        "with an underscore between each work. Characters other than letters and numbers are also<br>"
        "converted to underscore, and there is never more than one underscore between each word,<br>"
        "and the name will not start nor end with underscore.<br><br>"
        "<font color='red'>Example:</font> Controller (Xbox 360 Wireless Receiver For Windows) becomes<br>"
        "controller_xbox_360_wireless_receiver_for_windows.ini<br><br>"
        "Please visit <a href='http://fengestad.no/wp/fs-uae/custom-controller-configuration'>http://fengestad.no/wp/fs-uae/custom-controller-configuration</a> for an example<br>"
        "of INI Custom Controller Configuration file.";

void Amiga::on_joystickPort0CustomizePushButton_clicked()
{
    QFormLayout *formLayout = new QFormLayout;
    QLabel *label = new QLabel;
    label->setText("Insert your Joystick/GamePad name:");
    QLabel *label2 = new QLabel;
    label2->setTextFormat(Qt::RichText);
    label2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    label2->setOpenExternalLinks(true);
    label2->setText(pro);
    QLineEdit *nameLineEdit = new QLineEdit;
    QString actualJoystick=QString::fromStdString(inputConfiguration.getJoystickPort0String());
    if(!(actualJoystick.compare("mouse")==0)&&!(actualJoystick.compare("none")==0)&&!(actualJoystick.compare("keyboard")==0)&&(ui->joystickPort0ModelComboBox->findText(actualJoystick,Qt::MatchExactly)==-1)){
        nameLineEdit->setText(actualJoystick);}
    QPushButton *closeButton = new QPushButton("OK");
    QWidget *window = new QWidget;
    formLayout->addRow(label);
    formLayout->addRow(("Name:"), nameLineEdit);
    formLayout->addRow(label2);
    formLayout->addRow(closeButton);
    window->setLayout(formLayout);
    window->setWindowModality(Qt::ApplicationModal);
    connect(nameLineEdit, SIGNAL(textChanged(QString)),this, SLOT(customJoystick0Slot(QString)));
    connect(closeButton,SIGNAL(clicked()),window,SLOT(close()));
    window->show();
}
void Amiga::on_joystickPort1CusomizePushButton_clicked()
{
    QFormLayout *formLayout = new QFormLayout;
    QLabel *label = new QLabel;
    label->setText("Insert your Joystick/GamePad name:");
    QLabel *label2 = new QLabel;
    label2->setTextFormat(Qt::RichText);
    label2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    label2->setOpenExternalLinks(true);
    label2->setText(pro);
    QLineEdit *nameLineEdit = new QLineEdit;
    QString actualJoystick=QString::fromStdString(inputConfiguration.getJoystickPort1String());
    if(!(actualJoystick.compare("mouse")==0)&&!(actualJoystick.compare("none")==0)&&!(actualJoystick.compare("keyboard")==0)&&(ui->joystickPort1ModelComboBox->findText(actualJoystick,Qt::MatchExactly)==-1)){
        nameLineEdit->setText(actualJoystick);}
    QPushButton *closeButton = new QPushButton("OK");
    QWidget *window = new QWidget;
    formLayout->addRow(label);
    formLayout->addRow(("Name:"), nameLineEdit);
    formLayout->addRow(label2);
    formLayout->addRow(closeButton);
    window->setLayout(formLayout);
    window->setWindowModality(Qt::ApplicationModal);
    connect(nameLineEdit, SIGNAL(textChanged(QString)),this, SLOT(customJoystick1Slot(QString)));
    connect(closeButton,SIGNAL(clicked()),window,SLOT(close()));
    window->show();
}

void Amiga::on_joystickPort2CustomizePushButton_clicked()
{
    QFormLayout *formLayout = new QFormLayout;
    QLabel *label = new QLabel;
    label->setText("Insert your Joystick/GamePad name:");QLabel *label2 = new QLabel;
    label2->setTextFormat(Qt::RichText);
    label2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    label2->setOpenExternalLinks(true);
    label2->setText(pro);
    QLineEdit *nameLineEdit = new QLineEdit;
    QString actualJoystick=QString::fromStdString(inputConfiguration.getJoystickPort2String());
    if(!(actualJoystick.compare("mouse")==0)&&!(actualJoystick.compare("none")==0)&&!(actualJoystick.compare("keyboard")==0)&&(ui->joystickPort2ModelComboBox->findText(actualJoystick,Qt::MatchExactly)==-1)){
        nameLineEdit->setText(actualJoystick);}
    QPushButton *closeButton = new QPushButton("OK");
    QWidget *window = new QWidget;
    formLayout->addRow(label);
    formLayout->addRow(("Name:"), nameLineEdit);
    formLayout->addRow(label2);
    formLayout->addRow(closeButton);
    window->setLayout(formLayout);
    window->setWindowModality(Qt::ApplicationModal);
    connect(nameLineEdit, SIGNAL(textChanged(QString)),this, SLOT(customJoystick2Slot(QString)));
    connect(closeButton,SIGNAL(clicked()),window,SLOT(close()));
    window->show();
}
void Amiga::on_joystickPort3CustomizePushButton_clicked()
{
    QFormLayout *formLayout = new QFormLayout;
    QLabel *label = new QLabel;
    label->setText("Insert your Joystick/GamePad name:");QLabel *label2 = new QLabel;
    label2->setTextFormat(Qt::RichText);
    label2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    label2->setOpenExternalLinks(true);
    label2->setText(pro);
    QLineEdit *nameLineEdit = new QLineEdit;
    QString actualJoystick=QString::fromStdString(inputConfiguration.getJoystickPort3String());
    if(!(actualJoystick.compare("mouse")==0)&&!(actualJoystick.compare("none")==0)&&!(actualJoystick.compare("keyboard")==0)&&(ui->joystickPort3ModelComboBox->findText(actualJoystick,Qt::MatchExactly)==-1)){
        nameLineEdit->setText(actualJoystick);}
    QPushButton *closeButton = new QPushButton("OK");
    QWidget *window = new QWidget;
    formLayout->addRow(label);
    formLayout->addRow(("Name:"), nameLineEdit);
    formLayout->addRow(label2);
    formLayout->addRow(closeButton);
    window->setLayout(formLayout);
    window->setWindowModality(Qt::ApplicationModal);
    connect(nameLineEdit, SIGNAL(textChanged(QString)),this, SLOT(customJoystick3Slot(QString)));
    connect(closeButton,SIGNAL(clicked()),window,SLOT(close()));
    window->show();
}
void Amiga::on_joystickPort0CustomJoystickRadioButton_clicked()
{
    ui->joystickPort0ModelComboBox->setEnabled(false);
    ui->joystickPort0CustomizePushButton->setEnabled(true);
}

void Amiga::on_joystickPort0JoystickRadioButton_clicked()
{
    ui->joystickPort0ModelComboBox->setEnabled(true);
    ui->joystickPort0CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_0",ui->joystickPort0ModelComboBox->currentText().toStdString());
}

void Amiga::on_joystickPort0MouseRadioButton_clicked()
{
    ui->joystickPort0ModelComboBox->setEnabled(false);
    ui->joystickPort0CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_0","mouse");
}

void Amiga::on_joystickPort0KeyboardRadioButton_clicked()
{
    ui->joystickPort0ModelComboBox->setEnabled(false);
    ui->joystickPort0CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_0","keyboard");
}

void Amiga::on_joystickPort0NothingRadioButton_clicked()
{
    ui->joystickPort0ModelComboBox->setEnabled(false);
    ui->joystickPort0CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_0","none");
}

void Amiga::on_joystickPort0ModelComboBox_currentIndexChanged(const QString &arg1)
{
    inputConfiguration.setParameter("joystick_port_0",arg1.toStdString());
}

void Amiga::on_joystickPort1MouseRadioButton_clicked()
{
    ui->joystickPort1ModelComboBox->setEnabled(false);
    ui->joystickPort1CusomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_1","mouse");
}

void Amiga::on_joystickPort2MouseRadioButton_clicked()
{
    ui->joystickPort2ModelComboBox->setEnabled(false);
    ui->joystickPort2CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_2","mouse");
}

void Amiga::on_joystickPort3MouseRadioButton_clicked()
{
    ui->joystickPort3ModelComboBox->setEnabled(false);
    ui->joystickPort3CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_3","mouse");
}

void Amiga::on_joystickPort1KeyboardRadioButton_clicked()
{
    ui->joystickPort1ModelComboBox->setEnabled(false);
    ui->joystickPort1CusomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_1","keyboard");
}

void Amiga::on_joystickPort2KeyboardRadioButton_clicked()
{
    ui->joystickPort2ModelComboBox->setEnabled(false);
    ui->joystickPort2CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_2","keyboard");
}

void Amiga::on_joystickPort3KeyboardRadioButton_clicked()
{
    ui->joystickPort3ModelComboBox->setEnabled(false);
    ui->joystickPort3CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_3","keyboard");
}

void Amiga::on_joystickPort1JoystickRadioButton_clicked()
{
    ui->joystickPort1ModelComboBox->setEnabled(true);
    ui->joystickPort1CusomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_1",ui->joystickPort1ModelComboBox->currentText().toStdString());
}

void Amiga::on_joystickPort2JoystickRadioButton_clicked()
{
    ui->joystickPort2ModelComboBox->setEnabled(true);
    ui->joystickPort2CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_2",ui->joystickPort2ModelComboBox->currentText().toStdString());
}

void Amiga::on_joystickPort3JoystickRadioButton_clicked()
{
    ui->joystickPort3ModelComboBox->setEnabled(true);
    ui->joystickPort3CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_3",ui->joystickPort3ModelComboBox->currentText().toStdString());
}

void Amiga::on_joystickPort1ModelComboBox_currentIndexChanged(const QString &arg1)
{
    inputConfiguration.setParameter("joystick_port_1",arg1.toStdString());
}

void Amiga::on_joystickPort2ModelComboBox_currentIndexChanged(const QString &arg1)
{
    inputConfiguration.setParameter("joystick_port_2",arg1.toStdString());
}

void Amiga::on_joystickPort3ModelComboBox_currentIndexChanged(const QString &arg1)
{
    inputConfiguration.setParameter("joystick_port_3",arg1.toStdString());
}

void Amiga::on_joystickPort1CustomJoystickRadioButton_clicked()
{
    ui->joystickPort1ModelComboBox->setEnabled(false);
    ui->joystickPort1CusomizePushButton->setEnabled(true);
}

void Amiga::on_joystickPort2CustomJoystickRadioButton_clicked()
{
    ui->joystickPort2ModelComboBox->setEnabled(false);
    ui->joystickPort2CustomizePushButton->setEnabled(true);
}

void Amiga::on_joystickPort3CustomJoystickRadioButton_clicked()
{
    ui->joystickPort3ModelComboBox->setEnabled(false);
    ui->joystickPort3CustomizePushButton->setEnabled(true);
}

void Amiga::on_joystickPort1NothingRadioButton_clicked()
{
    ui->joystickPort1ModelComboBox->setEnabled(false);
    ui->joystickPort1CusomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_1","none");
}

void Amiga::on_joystickPort2NothingRadioButton_clicked()
{
    ui->joystickPort2ModelComboBox->setEnabled(false);
    ui->joystickPort2CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_2","none");
}

void Amiga::on_joystickPort3NothingRadioButton_clicked()
{
    ui->joystickPort3ModelComboBox->setEnabled(false);
    ui->joystickPort3CustomizePushButton->setEnabled(false);
    inputConfiguration.setParameter("joystick_port_3","none");
}
