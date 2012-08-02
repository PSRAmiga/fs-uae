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

#include <QApplication>
#include <QDesktopWidget>

#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
using namespace std;

Amiga::Amiga(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Amiga)
{
    ui->setupUi(this);

    //things to do onLoad
    ui->Setup->setCurrentIndex(0);
    //acquire current screen resolution
    ui->fullscreenResolutionXSpinBox->setValue(QApplication::desktop()->width());
    ui->fullscreenResolutionYSpinBox->setValue(QApplication::desktop()->height());
   //allow only numeric input
    ui->audioBufferLineEdit->setValidator(new QIntValidator(ui->audioBufferLineEdit));
    ui->serverPortLineEdit->setValidator(new QIntValidator(ui->serverPortLineEdit));

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
    if (!isEmptyString(ramConfiguration.getZorro3ConfigString()) && (chipsetConfiguration.getAmigaModelString().compare("A1200/020")==0 || chipsetConfiguration.getAmigaModelString().compare("A4000/040")==0)) {myfile << ramConfiguration.getZorro3ConfigString() << endl;}
    ////////////////////////////////////////////////////////////////check sul modello oppure fare una fx validate configuration prima di salvare e al caricamento da file??? /////////////////

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

    if ((!isEmptyString(cdromConfiguration.getCDRomDrive0ConfigString())) && (((chipsetConfiguration.getAmigaModelString().compare("CDTV")==0))||(chipsetConfiguration.getAmigaModelString().compare("CD32")==0))) {myfile << cdromConfiguration.getCDRomDrive0ConfigString() << endl;}
    if ((cdromConfiguration.getCDRomImageSize()>0) && (((chipsetConfiguration.getAmigaModelString().compare("CDTV")==0))||(chipsetConfiguration.getAmigaModelString().compare("CD32")==0))){
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

    //checkConfigurationConsistency() --> devo eliminare le configurazioni proibite che potrebbero essere venute fuori dal caricamento di un file manomeso

    saveConfigInFile(fileNameString);

}

int Amiga::getConfigurationAreaFromParameterName(string parameterName){
    if ((parameterName.compare("amiga_model")==0)||(parameterName.compare("accuracy")==0)||(parameterName.compare("kickstart_file")==0)||(parameterName.compare("kickstart_ext_file")==0)||(parameterName.compare("ntsc_mode")==0)) {
        return 1;
    } else if ((parameterName.compare("chip_memory")==0)||(parameterName.compare("slow_memory")==0)||(parameterName.compare("fast_memory")==0)||(parameterName.compare("zorro_iii_memory")==0)){
        return 2;
    } else if ((parameterName.substr(0,parameterName.length()-1).compare("floppy_drive_")==0)||(parameterName.substr(0,parameterName.length()-1).compare("floppy_image_")==0)||(parameterName.substr(0,parameterName.length()-2).compare("floppy_image_")==0)||(parameterName.compare("floppy_drive_volume")==0)||(parameterName.compare("floppy_drive_speed")==0)){
        return 3;
    } else if ((parameterName.substr(0,parameterName.length()-1).compare("cdrom_drive_")==0)||(parameterName.substr(0,parameterName.length()-1).compare("cdrom_image_")==0)||(parameterName.substr(0,parameterName.length()-2).compare("cdrom_image_")==0)){
        return 4;
    } else if ((parameterName.substr(0,parameterName.length()-1).compare("hard_drive_")==0)||
               ((parameterName.substr(0,string("hard_drive_").length()).compare("hard_drive_")==0)&&(parameterName.substr(string("hard_drive_").length()+1,parameterName.length()).compare("_label")==0))||
               ((parameterName.substr(0,string("hard_drive_").length()).compare("hard_drive_")==0)&&(parameterName.substr(string("hard_drive_").length()+1,parameterName.length()).compare("_read_only")==0))){
        return 5;
    } else if (false){ ///fare joystick!!!
        return 6;
    } else if ((parameterName.compare("fullscreen")==0)||(parameterName.compare("fullscreen_width")==0)||(parameterName.compare("fullscreen_height")==0)||
               (parameterName.compare("window_width")==0)||(parameterName.compare("window_height")==0)||(parameterName.compare("window_resizable")==0)||
               (parameterName.compare("fsaa")==0)||(parameterName.compare("keep_aspect")==0)||(parameterName.compare("scanlines")==0)||
               (parameterName.compare("rtg_scanlines")==0)||(parameterName.compare("scanlines_dark")==0)||(parameterName.compare("scanlines_light")==0)||
               (parameterName.compare("shader")==0)||(parameterName.compare("low_resolution")==0)||(parameterName.compare("line_doubling")==0)||
               (parameterName.compare("scale_x")==0)||(parameterName.compare("scale_y")==0)||(parameterName.compare("align_x")==0)||
               (parameterName.compare("align_y")==0)||(parameterName.compare("zoom")==0)||(parameterName.compare("texture_filter")==0)||
               (parameterName.compare("video_sync")==0)||(parameterName.compare("video_sync")==0)||(parameterName.compare("video_format")==0)||
               (parameterName.compare("texture_format")==0)||(parameterName.compare("viewport")==0)){
        return 7;
    } else if (false){ //fare theme
        return 8;
    } else if ((parameterName.compare("input_grab")==0)||(parameterName.compare("automatic_input_grab")==0)||(parameterName.compare("bsdsocket_library")==0)||
               (parameterName.compare("audio_buffer_target_bytes")==0)||(parameterName.compare("title")==0)||(parameterName.compare("sub_title")==0)||
               (parameterName.compare("netplay_server")==0)||(parameterName.compare("netplay_port")==0)||(parameterName.compare("netplay_tag")==0)||
               (parameterName.compare("base_dir")==0)||(parameterName.compare("kickstarts_dir")==0)||(parameterName.compare("save_states_dir")==0)||
               (parameterName.compare("floppy_overlays_dir")==0)||(parameterName.compare("flash_memory_dir")==0)||(parameterName.compare("controllers_dir")==0)||
               (parameterName.compare("logs_dir")==0)||(parameterName.compare("hard_drives_dir")==0)||(parameterName.compare("cdroms_dir")==0)||
               (parameterName.compare("floppies_dir")==0)||(parameterName.compare("netplay_password")==0)){
        return 9;
    } else {
        return -1;
    }
}

void Amiga::parseLine(string line){
    if (line.length()<=1) return;
    //fs-uae config file convention is "name = value"

    int separatorPosition=line.find_first_of(" = ");
    string parameterName=line.substr(0,separatorPosition);
    string parameterValue=line.substr(separatorPosition+3,line.length()-1);

    //bisogna capire in quale area di configurazione indirizzarlo
    //NB se non trovo nessun parametro con quel nome significa che il parametro non esiste (getConfigurationAreaFromParameterName ritorna -1)
    //MA se invece il parametro esiste ma non ha un valore valido se ne preoccupa l'area di configurazione

    int configArea=getConfigurationAreaFromParameterName(parameterName);
    if (configArea==1){
        chipsetConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==2){
        ramConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==3){
        floppyConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==4){
        cdromConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==5){
        hardDiskConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==6){
        //inputConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==7){
        graphicsConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==8){
        //themeConfiguration.setParameter(parameterName,parameterValue);
    } else if (configArea==9){
        miscConfiguration.setParameter(parameterName,parameterValue);
    }
}

bool Amiga::checkConfigurationConsistency()
{
    /*controlli da fare:

      NB la priorità di è da sx a dx nelle tab. devo far uscire un SI/NO che avvisa che sono state trovate Inconsistenze e non si può salvare/eseguire

      posso fare che se una cosa è disabilitata la svuoto/la setto al default?

    1-kickstart extended è abiiltato solo con CD32 e CDTV  --> quindi se model=CD32 devo cancellare/settare a DEFAULT la kickstart ext e tutti i parametri del CD
    2-CD è abilitato solo con CD32 e CDTV
    3-slowmemory 1.8MB è DIS-abilitato solo con A1200/020, A4000/040 e CD32
    4-zorro3 è abilitato solo con A1200/020 e A4000/040
    5-fastmemory è DIS-abilitato se chipsetram=4MB o 8MB
    6-with borders è disabilitato con full e auto

    */
    return true;
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
    cdromConfiguration.setToDefaultConfiguration();
    hardDiskConfiguration.setToDefaultConfiguration();
    graphicsConfiguration.setToDefaultConfiguration();
    miscConfiguration.setToDefaultConfiguration();
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

    //checkConfigurationConsistency() --> devo eliminare le configurazioni proibite che potrebbero essere venute fuori dal caricamento di un file manomeso

    //lo devo fare per ogni configuration area
    updateGraphicsFromInternalConfiguration();
}

void Amiga::on_loadDefaultValuesToolButton_clicked()
{
    chipsetConfiguration.setToDefaultConfiguration();
    ramConfiguration.setToDefaultConfiguration();
    floppyConfiguration.setToDefaultConfiguration();
    cdromConfiguration.setToDefaultConfiguration();
    hardDiskConfiguration.setToDefaultConfiguration();
    graphicsConfiguration.setToDefaultConfiguration();
    miscConfiguration.setToDefaultConfiguration();
    /////////////////////////////////////////////ecc per tutti gli altri///////////////////////////////////////////////////

    //devo DISABILITARE/SVUOTARE KICK_EXT_DIR e tutte le cose che di default sarebbero disabilitate/vuote!
    setFastMemoryDisabled(false);
    // ui->floppySwappingImagesListWidget->clear();

    updateGraphicsFromInternalConfiguration();

}

void Amiga::on_runConfigButton_clicked()
{
    //fare check consistenza!!! ////////////////////////////////////////////////////////////////////
    saveConfigInFile(".current.fs-uae");

    /*int returnValue=system("fs-uae .current.fs-uae");
    if (returnValue!=0)
    {
        QMessageBox::about(this, tr("Error"),tr("Ops...something went wrong :-("));
    }*/
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
        //aggiorno la lista grafica
        //  ui->floppySwappingImagesListWidget->addItem(fileNames.at(i));
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
    QColor color = QColorDialog::getColor(Qt::black, this);
    ui->fadeColorPushButton->setText(color.name());
    ui->fadeColorPushButton->setStyleSheet(QString("background-color: ")+color.name());
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
